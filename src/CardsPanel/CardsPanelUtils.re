open CardsPanel;

let randomizeOrder = elements =>
  elements
  |> List.map(c =>
       (Js.Date.now() |> int_of_float |> Random.init |> Random.bits, c)
     )
  |> List.sort(compare)
  |> List.map(snd);

let makeCards = images =>
  images |> List.map(image => {image, isFlipped: false, isMatched: false});

let deriveCardsFromImageData = imageData =>
  imageData
  |> List.append(imageData)
  |> randomizeOrder
  |> makeCards
  |> Array.of_list;