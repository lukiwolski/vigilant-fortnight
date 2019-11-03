'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Random = require("bs-platform/lib/js/random.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");

function randomizeOrder(elements) {
  return List.map((function (prim) {
                return prim[1];
              }), List.sort(Caml_obj.caml_compare, List.map((function (c) {
                        return /* tuple */[
                                Random.bits(Random.init(Date.now() | 0)),
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

function deriveCardsFromImageData(imageData) {
  return $$Array.of_list(makeCards(randomizeOrder(List.append(imageData, imageData))));
}

exports.randomizeOrder = randomizeOrder;
exports.makeCards = makeCards;
exports.deriveCardsFromImageData = deriveCardsFromImageData;
/* No side effect */
