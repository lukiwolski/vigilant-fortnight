open GetImages;

module Styles = {
  open Css;

  let app =
    style([
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      height(100. |> pct),
    ]);
};

type loadingState =
  | None
  | Some(array(CardsPanel.card))
  | Error;

[@react.component]
let make = () => {
  let (cards, setCards) = React.useState(() => None);
  let (refetchImages, setRefetchImages) = React.useState(() => false);

  React.useEffect1(
    () => {
      makeQuery(queryParams |> mapParamsToQuery)
      |> Js.Promise.then_(imageData => {
           setCards(_prev =>
             Some(CardsPanelUtils.deriveCardsFromImageData(imageData))
           );
           Js.Promise.resolve();
         })
      |> Js.Promise.catch(err => {
           Js.log("An error occurred: " ++ Js.String.make(err));
           setCards(_prev => Error);
           Js.Promise.resolve();
         })
      |> ignore;

      None;
    },
    [|refetchImages|],
  );

  <div className=Styles.app>
    {switch (cards) {
     | Some(cards) => <CardsPanel cards />
     | None => React.string("Fetching images")
     | Error => React.string("Failed fetching images")
     }}
  </div>;
};