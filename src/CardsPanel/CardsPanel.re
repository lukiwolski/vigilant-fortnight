type card = {
  image: GetImages.image,
  isFlipped: bool,
  isMatched: bool,
};

module Styles = {
  open Css;

  let card = (~isFlipped, ~isMatched) =>
    style([
      backgroundSize(isFlipped ? cover : size(px(0), px(0))),
      backgroundColor(isMatched ? green : transparent),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
      flexBasis(pct(21.)),
      margin(px(16)),
      width(px(140)),
      height(px(140)),
      backgroundPosition(pct(50.), pct(50.)),
    ]);

  let cardContainer = style([display(flexBox), flexWrap(wrap)]);
};

type state = {cards: list(card)};

type action =
  | Reset
  | Flip(int, string);

let randomizeOrder = elements =>
  elements
  |> List.map(c => (Random.bits(), c))
  |> List.sort(compare)
  |> List.map(snd);

let makeCards = images =>
  images |> List.map(image => {image, isFlipped: false, isMatched: false});

[@react.component]
let make = (~imageData) => {
  let cards =
    imageData |> List.append(imageData) |> randomizeOrder |> makeCards;

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Flip(nth, id) => state |> List.mapi((n, card) => card)
        },
      {
        cards;
      },
    );

  <div>
    {state
     |> List.mapi((index, {image, isFlipped, isMatched}) => {
          let {id, source}: GetImages.image = image;
          <div
            key={j|$id-$index|j}
            className={Styles.card(~isFlipped, ~isMatched)}
            style={ReactDOMRe.Style.make(
              ~backgroundImage={j|url($source)|j},
              (),
            )}>
            {React.string(image.source)}
          </div>;
        })
     |> Array.of_list
     |> React.array}
  </div>;
};