'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var GetImages$ReasonReactExamples = require("./GetImages.bs.js");
var CardsPanel$ReasonReactExamples = require("./CardsPanel/CardsPanel.bs.js");

function App(Props) {
  var match = React.useState((function () {
          return ;
        }));
  var setImageData = match[1];
  var imageData = match[0];
  React.useEffect((function () {
          GetImages$ReasonReactExamples.makeQuery(GetImages$ReasonReactExamples.mapParamsToQuery(GetImages$ReasonReactExamples.queryParams)).then((function (imageData) {
                    Curry._1(setImageData, (function (_prev) {
                            return imageData;
                          }));
                    return Promise.resolve(/* () */0);
                  })).catch((function (err) {
                  console.log("An error occurred: " + String(err));
                  return Promise.resolve(/* () */0);
                }));
          return ;
        }), ([]));
  if (imageData !== undefined) {
    return React.createElement(CardsPanel$ReasonReactExamples.make, {
                imageData: imageData
              });
  } else {
    return "Loading...";
  }
}

var make = App;

exports.make = make;
/* react Not a pure module */
