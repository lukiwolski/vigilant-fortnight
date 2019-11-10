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
  isCompleted: option(bool),
};

module Styles = {
  open Css;

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

  let cardWrapper =
    style([
      focus([outlineColor(transparent)]),
      firstChild([gridRow(1, 1), gridColumn(1, 1)]),
      position(relative),
      borderRadius(8 |> px),
      overflow(hidden),
      border(0 |> px, `none, transparent),
      backgroundColor(transparent),
    ]);
};

let initialLastRevealed = ((-1), "");

[@react.component]
let make = (~items: array(card)) => {
  let ({cards, lastRevealed, isLocked, isCompleted}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Match(id) =>
          let cards =
            state.cards
            |> Array.map(card =>
                 card.image.id === id
                   ? {...card, isFlipped: true, isMatched: true} : card
               );
          let isCompleted =
            Some(
              cards |> Array.to_list |> List.for_all(card => card.isMatched),
            );

          {...state, cards, lastRevealed: initialLastRevealed, isCompleted};
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
            ...state,
            cards:
              state.cards
              |> Array.mapi((i, card) =>
                   i === index ? {...card, isFlipped: true} : card
                 ),
            lastRevealed: (index, id),
            isLocked,
          }
        | Mismatch(lastIndex, index) => {
            ...state,
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
      {
        cards: items,
        lastRevealed: initialLastRevealed,
        isLocked: None,
        isCompleted: None,
      },
    );
  let (lastIndex, lastId) = lastRevealed;

  <div className=Styles.cardContainer>
    {cards
     |> Array.mapi((index, {image: {id, source}, isFlipped, isMatched}) => {
          let sameItem = lastIndex === index;
          let matchingItems = lastId === id;
          let isSameRevealed = lastRevealed == initialLastRevealed;

          <button
            key={j|$id-$index|j}
            disabled={isMatched || isLocked === Some(true)}
            onClick={_event =>
              switch (sameItem, matchingItems, isSameRevealed) {
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
            className=Styles.cardWrapper>
            <Card faceSource=source isFlipped />
          </button>;
        })
     |> React.array}
    {isCompleted === Some(true)
       ? React.string("Hooray good job") : React.null}
  </div>;
};