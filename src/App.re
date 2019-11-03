open GetImages;

[@react.component]
let make = () => {
  let (imageData, setImageData) = React.useState(() => None);

  React.useEffect0(() => {
    makeQuery(queryParams |> mapParamsToQuery)
    |> Js.Promise.then_(imageData => {
         setImageData(_prev => Some(imageData));
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(err => {
         Js.log("An error occurred: " ++ Js.String.make(err));
         Js.Promise.resolve();
       })
    |> ignore;

    None;
  });

  let images =
    switch (imageData) {
    | Some(imageData) =>
      <CardsPanel
        items={CardsPanelUtils.deriveCardsFromImageData(imageData)}
      />
    | None => React.string("Loading...")
    };

  images;
};