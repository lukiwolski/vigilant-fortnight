Css.(global("body", [margin(px(0))]));
Css.(global("html, body, body > div", [height(100. |> pct)]));

ReactDOMRe.renderToElementWithId(<App />, "index");