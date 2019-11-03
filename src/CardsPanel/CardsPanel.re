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

  let card = (~isFlipped, ~isMatched) =>
    style([
      backgroundSize(isFlipped ? cover : size(0 |> px, 0 |> px)),
      backgroundColor(isMatched ? green : transparent),
      backgroundPosition(50. |> pct, 50. |> pct),
      firstChild([gridRow(1, 1), gridColumn(1, 1)]),
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
            className={Styles.card(~isFlipped, ~isMatched)}
            style={ReactDOMRe.Style.make(
              ~backgroundImage={j|url($source)|j},
              (),
            )}>
            {React.string(string_of_int(index + 1))}
          </button>
        )
     |> React.array}
  </div>;
};