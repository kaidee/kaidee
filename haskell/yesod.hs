import Yesod

data HelloWorld = HelloWorld

mkYesod "HelloWorld" [parseRoutes|
/ HomeR GET
|]

instance Yesod HelloWorld

getHomeR :: Handler RepHtml
getHomeR = defaultLayout [whamlet|
<h3> Hello World!
    <p> This is my first web page
|]

main :: IO ()
main = warpDebug 3000 HelloWorld