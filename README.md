# ReasonReact Template & Examples

https://vigilant-fortnight.vercel.app/indexProduction.html

## Run

```sh
npm install
npm run server
# in a new tab
npm start
```

Open a new web page to `http://localhost:8000/`. Change any `.re` file in `src` to see the page auto-reload. **You don't need any bundler when you're developing**!

**How come we don't need any bundler during development**? We highly encourage you to open up `index.html` to check for yourself!

# Features Used

|                           | Blinking Greeting | Reducer from ReactJS Docs | Fetch Dog Pictures | Reason Using JS Using Reason |
|---------------------------|------------------|----------------------------|--------------------|------------------------------|
| No props                  |                  | ✓                          |                    |                             |
| Has props                 |                  |                            |                    | ✓                           |
| Children props            | ✓                |                            |                    |                             |
| No state                  |                  |                            |                    | ✓                           |
| Has state                 | ✓                |                            |  ✓                 |                             |
| Has state with useReducer |                  | ✓                          |                    |                             |
| ReasonReact using ReactJS |                  |                            |                    | ✓                           |
| ReactJS using ReasonReact |                  |                            |                    | ✓                           |
| useEffect                 | ✓                |                            |  ✓                |                             |
| Dom attribute             | ✓                | ✓                          |                   | ✓                           |
| Styling                   | ✓                | ✓                          |  ✓                | ✓                           |
| React.array               |                  |                            |  ✓                 |                             |

# Bundle for Production

We've included a convenience `UNUSED_webpack.config.js`, in case you want to ship your project to production. You can rename and/or remove that in favor of other bundlers, e.g. Rollup.

We've also provided a barebone `indexProduction.html`, to serve your bundle.

```sh
npm install webpack webpack-cli
# rename file
mv UNUSED_webpack.config.js webpack.config.js
# call webpack to bundle for production
./node_modules/.bin/webpack
open indexProduction.html
```
