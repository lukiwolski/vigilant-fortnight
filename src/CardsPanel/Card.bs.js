'use strict';

var Css = require("bs-css/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactSpring = require("react-spring");

var Animated = { };

var card = Css.style(/* :: */[
      Css.position(Css.absolute),
      /* :: */[
        Css.left(Css.px(0)),
        /* :: */[
          Css.top(Css.px(0)),
          /* :: */[
            Css.height(Css.pct(100)),
            /* :: */[
              Css.width(Css.pct(100)),
              /* :: */[
                Css.unsafe("will-change", "transform, opacity;"),
                /* :: */[
                  Css.backgroundSize(Css.cover),
                  /* [] */0
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var backFace = Css.style(/* :: */[
      Css.unsafe("background-image", "linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),\n  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),\n  linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),\n  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),\n  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a),\n  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a);\n  background-size:80px 140px;\n  background-position: 0 0, 0 0, 40px 70px, 40px 70px, 0 0, 40px 70px;"),
      /* [] */0
    ]);

function frontFace(faceSource) {
  return Css.style(/* :: */[
              Css.backgroundImage(/* `url */[
                    5843823,
                    faceSource
                  ]),
              /* [] */0
            ]);
}

var Styles = {
  card: card,
  backFace: backFace,
  frontFace: frontFace
};

function Card(Props) {
  var faceSource = Props.faceSource;
  var isFlipped = Props.isFlipped;
  var match = ReactSpring.useSpring((function (param) {
          return {
                  opacity: 0,
                  transform: "perspective(600px) rotateX(0deg)"
                };
        }));
  var set = match[1];
  var springProps = match[0];
  React.useEffect((function () {
          var rotateX = isFlipped ? 180 : 0;
          var transform = "perspective(600px) rotateX(" + (String(rotateX) + "deg)");
          Curry._1(set, {
                opacity: isFlipped ? 1 : 0,
                transform: transform
              });
          return ;
        }), /* array */[isFlipped]);
  var frontFace$1 = frontFace(faceSource);
  return React.createElement(React.Fragment, undefined, React.createElement(ReactSpring.animated.div, {
                  class: "" + (String(card) + (" " + (String(backFace) + ""))),
                  style: {
                    opacity: springProps.opacity.interpolate((function (o) {
                            return 1 - o;
                          })),
                    transform: springProps.transform
                  }
                }), React.createElement(ReactSpring.animated.div, {
                  class: "" + (String(card) + (" " + (String(frontFace$1) + ""))),
                  style: {
                    opacity: springProps.opacity,
                    transform: springProps.transform.interpolate((function (t) {
                            return "" + (String(t) + " rotateX(180deg)");
                          }))
                  }
                }));
}

var make = Card;

exports.Animated = Animated;
exports.Styles = Styles;
exports.make = make;
/* card Not a pure module */
