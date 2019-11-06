type card = {
  image: GetImages.image,
  isFlipped: bool,
  isMatched: bool,
};

type revealedCard = (int, string);

type action =
  | Match(string)
  | Mismatch(int, int)
  | Reveal(int, string, option(bool))
  | Hide(int);

type state = {
  cards: array(card),
  lastRevealed: revealedCard,
  isLocked: option(bool),
};

module Styles = {
  open Css;

  let card = (~isFlipped) =>
    style([
      focus([outlineColor(transparent)]),
      firstChild([gridRow(1, 1), gridColumn(1, 1)]),
      position(relative),
      transformStyle(`preserve3d),
      unsafe("transform-origin", "center right"),
      unsafe("transition", "transform .3s"),
      border(2 |> px, solid, black),
      borderRadius(8 |> px),
      transforms([
        `translateX((!isFlipped ? (-100.) : 0.) |> pct),
        `rotateY((!isFlipped ? (-180.) : 0.) |> deg),
      ]),
      unsafe(
        "background-image",
        "linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a),
  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a);
  background-size:80px 140px;
  background-position: 0 0, 0 0, 40px 70px, 40px 70px, 0 0, 40px 70px;",
      ),
    ]);

  let cardFace = () =>
    style([
      position(absolute),
      width(100. |> pct),
      height(100. |> pct),
      backfaceVisibility(hidden),
      backgroundPosition(50. |> pct, 50. |> pct),
      backgroundSize(cover),
      left(0 |> px),
      top(0 |> px),
      borderRadius(8 |> px),
    ]);

  let cardContainer =
    style([
      display(`grid),
      gridTemplateColumns([
        `repeat((`autoFill, `minmax((`rem(12.), 1. |> fr)))),
      ]),
      unsafe("grid-auto-rows", "1fr"),
      gridGap(8 |> px),
      maxWidth(824 |> px),
      marginLeft(`auto),
      marginRight(`auto),
      before([
        contentRule(""),
        width(zero),
        paddingBottom(`percent(100.)),
        gridRow(1, 1),
        gridColumn(1, 1),
      ]),
    ]);
};

let initialLastRevealed = ((-1), "");

[@react.component]
let make = (~items: array(card)) => {
  let ({cards, lastRevealed, isLocked}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Match(id) => {
            ...state,
            cards:
              state.cards
              |> Array.map(card =>
                   card.image.id === id
                     ? {...card, isFlipped: true, isMatched: true} : card
                 ),
            lastRevealed: initialLastRevealed,
          }
        | Hide(index) => {
            ...state,
            cards:
              state.cards
              |> Array.mapi((i, card) =>
                   index === i ? {...card, isFlipped: false} : card
                 ),
            lastRevealed: initialLastRevealed,
          }
        | Reveal(index, id, isLocked) => {
            cards:
              state.cards
              |> Array.mapi((i, card) =>
                   i === index ? {...card, isFlipped: true} : card
                 ),
            lastRevealed: (index, id),
            isLocked,
          }
        | Mismatch(lastIndex, index) => {
            cards:
              state.cards
              |> Array.mapi((i, card) =>
                   i === index || i === lastIndex
                     ? {...card, isFlipped: false} : card
                 ),
            lastRevealed: initialLastRevealed,
            isLocked: None,
          }
        },
      {cards: items, lastRevealed: initialLastRevealed, isLocked: None},
    );
  let (lastIndex, lastId) = lastRevealed;

  <div className=Styles.cardContainer>
    {cards
     |> Array.mapi((index, {image: {id, source}, isFlipped, isMatched}) =>
          <button
            key={j|$id-$index|j}
            disabled={isMatched || isLocked === Some(true)}
            onClick={_event =>
              switch (
                lastIndex === index,
                lastId === id,
                lastRevealed == initialLastRevealed,
              ) {
              | (true, _, _) => dispatch(Hide(index))
              | (false, true, _) => dispatch(Match(id))
              | (false, false, true) => dispatch(Reveal(index, id, None))
              | (false, false, false) =>
                Js.Global.setTimeout(
                  () => dispatch(Mismatch(lastIndex, index)),
                  1000,
                )
                |> ignore;
                dispatch(Reveal(index, id, Some(true)));
              }
            }
            className={Styles.card(~isFlipped)}>
            <div
              className={Styles.cardFace()}
              style={ReactDOMRe.Style.make(
                ~backgroundImage={j|url($source)|j},
                (),
              )}
            />
          </button>
        )
     |> React.array}
  </div>;
};