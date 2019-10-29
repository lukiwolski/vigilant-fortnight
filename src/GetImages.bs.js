'use strict';

var List = require("bs-platform/lib/js/list.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function item(json) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.string, json),
          /* source */Json_decode.at(/* :: */[
                  "urls",
                  /* :: */[
                    "thumb",
                    /* [] */0
                  ]
                ], Json_decode.string)(json)
        ];
}

function all(param) {
  return Json_decode.list(item, param);
}

var Decode = {
  item: item,
  all: all
};

function mapParamsToQuery(params) {
  return List.fold_left((function (init, param) {
                return "" + (String(init) + ("" + (String(param[0]) + ("=" + (String(param[1]) + "&")))));
              }), "https://api.unsplash.com/photos/random?", params);
}

function makeQuery(queryUrl) {
  return fetch(queryUrl).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Json_decode.list(item, json));
              }));
}

var queryParams = /* :: */[
  /* tuple */[
    "client_id",
    "7a74496f4b9c20ff2ce556787f60b9a618ae5f0618a38c8658083c29ebc0f193"
  ],
  /* :: */[
    /* tuple */[
      "query",
      "cat"
    ],
    /* :: */[
      /* tuple */[
        "count",
        "8"
      ],
      /* :: */[
        /* tuple */[
          "orientation",
          "landscape"
        ],
        /* [] */0
      ]
    ]
  ]
];

exports.Decode = Decode;
exports.queryParams = queryParams;
exports.mapParamsToQuery = mapParamsToQuery;
exports.makeQuery = makeQuery;
/* No side effect */
