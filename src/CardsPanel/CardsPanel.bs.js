'use strict';

var Css = require("bs-css/src/Css.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");

function card(isFlipped, isMatched) {
  return Css.style(/* :: */[
              Css.backgroundSize(isFlipped ? Css.cover : Css.size(Css.px(0), Css.px(0))),
              /* :: */[
                Css.backgroundColor(isMatched ? Css.green : Css.transparent),
                /* :: */[
                  Css.backgroundPosition(Css.pct(50), Css.pct(50)),
                  /* :: */[
                    Css.firstChild(/* :: */[
                          Css.gridRow(1, 1),
                          /* :: */[
                            Css.gridColumn(1, 1),
                            /* [] */0
                          ]
                        ]),
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

var cardContainer = Css.style(/* :: */[
      Css.display(/* grid */-999565626),
      /* :: */[
        Css.gridTemplateColumns(/* :: */[
              /* `repeat */[
                108828507,
                /* tuple */[
                  /* autoFill */652328338,
                  /* `minmax */[
                    -754859950,
                    /* tuple */[
                      /* `rem */[
                        5691738,
                        12
                      ],
                      Css.fr(1)
                    ]
                  ]
                ]
              ],
              /* [] */0
            ]),
        /* :: */[
          Css.unsafe("grid-auto-rows", "1fr"),
          /* :: */[
            Css.gridGap(Css.px(8)),
            /* :: */[
              Css.maxWidth(Css.px(824)),
              /* :: */[
                Css.marginLeft(/* auto */-1065951377),
                /* :: */[
                  Css.marginRight(/* auto */-1065951377),
                  /* :: */[
                    Css.before(/* :: */[
                          Css.contentRule(""),
                          /* :: */[
                            Css.width(Css.zero),
                            /* :: */[
                              Css.paddingBottom(/* `percent */[
                                    -119887163,
                                    100
                                  ]),
                              /* :: */[
                                Css.gridRow(1, 1),
                                /* :: */[
                                  Css.gridColumn(1, 1),
                                  /* [] */0
                                ]
                              ]
                            ]
                          ]
                        ]),
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var Styles = {
  card: card,
  cardContainer: cardContainer
};

var initialLastRevealed = /* tuple */[
  -1,
  ""
];

function CardsPanel(Props) {
  var items = Props.items;
  var match = React.useReducer((function (state, action) {
          switch (action.tag | 0) {
            case /* Match */0 :
                var id = action[0];
                return /* record */[
                        /* cards */$$Array.map((function (card) {
                                var match = card[/* image */0][/* id */0] === id;
                                if (match) {
                                  return /* record */[
                                          /* image */card[/* image */0],
                                          /* isFlipped */true,
                                          /* isMatched */true
                                        ];
                                } else {
                                  return card;
                                }
                              }), state[/* cards */0]),
                        /* lastRevealed */initialLastRevealed,
                        /* isLocked */state[/* isLocked */2]
                      ];
            case /* Mismatch */1 :
                var index = action[1];
                var lastIndex = action[0];
                return /* record */[
                        /* cards */$$Array.mapi((function (i, card) {
                                var match = i === index || i === lastIndex;
                                if (match) {
                                  return /* record */[
                                          /* image */card[/* image */0],
                                          /* isFlipped */false,
                                          /* isMatched */card[/* isMatched */2]
                                        ];
                                } else {
                                  return card;
                                }
                              }), state[/* cards */0]),
                        /* lastRevealed */initialLastRevealed,
                        /* isLocked */undefined
                      ];
            case /* Reveal */2 :
                var index$1 = action[0];
                return /* record */[
                        /* cards */$$Array.mapi((function (i, card) {
                                var match = i === index$1;
                                if (match) {
                                  return /* record */[
                                          /* image */card[/* image */0],
                                          /* isFlipped */true,
                                          /* isMatched */card[/* isMatched */2]
                                        ];
                                } else {
                                  return card;
                                }
                              }), state[/* cards */0]),
                        /* lastRevealed : tuple */[
                          index$1,
                          action[1]
                        ],
                        /* isLocked */action[2]
                      ];
            case /* Hide */3 :
                var index$2 = action[0];
                return /* record */[
                        /* cards */$$Array.mapi((function (i, card) {
                                var match = index$2 === i;
                                if (match) {
                                  return /* record */[
                                          /* image */card[/* image */0],
                                          /* isFlipped */false,
                                          /* isMatched */card[/* isMatched */2]
                                        ];
                                } else {
                                  return card;
                                }
                              }), state[/* cards */0]),
                        /* lastRevealed */initialLastRevealed,
                        /* isLocked */state[/* isLocked */2]
                      ];
            
          }
        }), /* record */[
        /* cards */items,
        /* lastRevealed */initialLastRevealed,
        /* isLocked */undefined
      ]);
  var match$1 = match[0];
  var lastRevealed = match$1[/* lastRevealed */1];
  var lastId = lastRevealed[1];
  var lastIndex = lastRevealed[0];
  var dispatch = match[1];
  var isLocked = match$1[/* isLocked */2];
  return React.createElement("div", {
              className: cardContainer
            }, $$Array.mapi((function (index, param) {
                    var isMatched = param[/* isMatched */2];
                    var match = param[/* image */0];
                    var id = match[/* id */0];
                    return React.createElement("button", {
                                key: "" + (String(id) + ("-" + (String(index) + ""))),
                                className: card(param[/* isFlipped */1], isMatched),
                                style: {
                                  backgroundImage: "url(" + (String(match[/* source */1]) + ")")
                                },
                                disabled: isMatched || isLocked === true,
                                onClick: (function (_event) {
                                    var match = lastIndex === index;
                                    var match$1 = lastId === id;
                                    var match$2 = Caml_obj.caml_equal(lastRevealed, initialLastRevealed);
                                    if (match) {
                                      return Curry._1(dispatch, /* Hide */Block.__(3, [index]));
                                    } else if (match$1) {
                                      return Curry._1(dispatch, /* Match */Block.__(0, [id]));
                                    } else if (match$2) {
                                      return Curry._1(dispatch, /* Reveal */Block.__(2, [
                                                    index,
                                                    id,
                                                    undefined
                                                  ]));
                                    } else {
                                      setTimeout((function (param) {
                                              return Curry._1(dispatch, /* Mismatch */Block.__(1, [
                                                            lastIndex,
                                                            index
                                                          ]));
                                            }), 1000);
                                      return Curry._1(dispatch, /* Reveal */Block.__(2, [
                                                    index,
                                                    id,
                                                    true
                                                  ]));
                                    }
                                  })
                              }, String(index + 1 | 0));
                  }), match$1[/* cards */0]));
}

var make = CardsPanel;

exports.Styles = Styles;
exports.initialLastRevealed = initialLastRevealed;
exports.make = make;
/* cardContainer Not a pure module */
