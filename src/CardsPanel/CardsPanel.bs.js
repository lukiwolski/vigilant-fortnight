'use strict';

var Css = require("bs-css/src/Css.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Random = require("bs-platform/lib/js/random.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function card(isFlipped, isMatched) {
  return Css.style(/* :: */[
              Css.backgroundSize(isFlipped ? Css.cover : Css.size(Css.px(0), Css.px(0))),
              /* :: */[
                Css.backgroundColor(isMatched ? Css.green : Css.transparent),
                /* :: */[
                  Css.display(Css.flexBox),
                  /* :: */[
                    Css.alignItems(Css.center),
                    /* :: */[
                      Css.justifyContent(Css.center),
                      /* :: */[
                        Css.flexBasis(Css.pct(21)),
                        /* :: */[
                          Css.margin(Css.px(16)),
                          /* :: */[
                            Css.width(Css.px(140)),
                            /* :: */[
                              Css.height(Css.px(140)),
                              /* :: */[
                                Css.backgroundPosition(Css.pct(50), Css.pct(50)),
                                /* [] */0
                              ]
                            ]
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

var cardContainer = Css.style(/* :: */[
      Css.display(Css.flexBox),
      /* :: */[
        Css.flexWrap(Css.wrap),
        /* [] */0
      ]
    ]);

var Styles = {
  card: card,
  cardContainer: cardContainer
};

function randomizeOrder(elements) {
  return List.map((function (prim) {
                return prim[1];
              }), List.sort(Caml_obj.caml_compare, List.map((function (c) {
                        return /* tuple */[
                                Random.bits(/* () */0),
                                c
                              ];
                      }), elements)));
}

function makeCards(images) {
  return List.map((function (image) {
                return /* record */[
                        /* image */image,
                        /* isFlipped */false,
                        /* isMatched */false
                      ];
              }), images);
}

function CardsPanel(Props) {
  var imageData = Props.imageData;
  var cards = makeCards(randomizeOrder(List.append(imageData, imageData)));
  var match = React.useReducer((function (state, action) {
          if (action) {
            return List.mapi((function (n, card) {
                          return card;
                        }), state);
          } else {
            throw [
                  Caml_builtin_exceptions.match_failure,
                  /* tuple */[
                    "CardsPanel.re",
                    50,
                    8
                  ]
                ];
          }
        }), cards);
  return React.createElement("div", undefined, $$Array.of_list(List.mapi((function (index, param) {
                        var image = param[/* image */0];
                        return React.createElement("div", {
                                    key: "" + (String(image[/* id */0]) + ("-" + (String(index) + ""))),
                                    className: card(param[/* isFlipped */1], param[/* isMatched */2]),
                                    style: {
                                      backgroundImage: "url(" + (String(image[/* source */1]) + ")")
                                    }
                                  }, image[/* source */1]);
                      }), match[0])));
}

var make = CardsPanel;

exports.Styles = Styles;
exports.randomizeOrder = randomizeOrder;
exports.makeCards = makeCards;
exports.make = make;
/* cardContainer Not a pure module */
