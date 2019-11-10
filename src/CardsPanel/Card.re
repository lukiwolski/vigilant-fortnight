[@bs.deriving abstract]
type spring = {
  opacity: float,
  transform: string,
};

module Animated = {
  [@bs.module "react-spring"]
  external useSpring: ('c => spring) => ('a, 'b) = "useSpring";

  [@bs.module "react-spring"] [@react.component] [@bs.scope "animated"]
  external make: (~_class: string, ~style: spring) => React.element = "div";
};

module Styles = {
  open Css;

  let card =
    style([
      position(absolute),
      left(0 |> px),
      top(0 |> px),
      height(100. |> pct),
      width(100. |> pct),
      unsafe("will-change", "transform, opacity;"),
      backgroundSize(cover),
    ]);

  let backFace =
    style([
      unsafe(
        "background-image",
        "linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(30deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(150deg, #445 12%, transparent 12.5%, transparent 87%, #445 87.5%, #445),
  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a),
  linear-gradient(60deg, #99a 25%, transparent 25.5%, transparent 75%, #99a 75%, #99a);
  background-size:80px 140px;
  background-position: 0 0, 0 0, 40px 70px, 40px 70px, 0 0, 40px 70px;",
      ),
    ]);

  let frontFace = (~faceSource) =>
    style([backgroundImage(`url(faceSource))]);
};

[@react.component]
let make = (~faceSource: string, ~isFlipped: bool) => {
  let (springProps, set) =
    Animated.useSpring(() =>
      spring(~opacity=0., ~transform="perspective(600px) rotateX(0deg)")
    );

  React.useEffect1(
    () => {
      let rotateX = isFlipped ? 180 : 0;
      let transform = {j|perspective(600px) rotateX($(rotateX)deg)|j};
      set(spring(~opacity=isFlipped ? 1. : 0., ~transform)) |> ignore;

      None;
    },
    [|isFlipped|],
  );

  let card = Styles.card;
  let backFace = Styles.backFace;
  let frontFace = Styles.frontFace(~faceSource);
  <>
    <Animated
      _class={j|$card $backFace|j}
      style={spring(
        ~opacity=springProps##opacity##interpolate(o => 1. -. o),
        ~transform=springProps##transform,
      )}
    />
    <Animated
      _class={j|$card $frontFace|j}
      style={spring(
        ~opacity=springProps##opacity,
        ~transform=
          springProps##transform##interpolate(t => {j|$t rotateX(180deg)|j}),
      )}
    />
  </>;
};