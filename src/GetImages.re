type image = {
  id: string,
  source: string,
};

module Decode = {
  let item = json => {
    Json.Decode.{
      id: json |> field("id", string),
      source: json |> at(["urls", "thumb"], string),
    };
  };

  let all = Json.Decode.list(item);
};

let queryParams = [
  (
    "client_id",
    "7a74496f4b9c20ff2ce556787f60b9a618ae5f0618a38c8658083c29ebc0f193",
  ),
  ("query", "cat"),
  ("count", "8"),
  ("orientation", "landscape"),
];

let mapParamsToQuery = params =>
  params
  |> List.fold_left(
       (init, (key, value)) => {j|$init$key=$value&|j},
       "https://api.unsplash.com/photos/random?",
     );

let makeQuery = queryUrl =>
  Js.Promise.(
    Fetch.fetch(queryUrl)
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Decode.all |> resolve)
  );