#! /bin/sh

echo 'Content-type: text/html'
echo

printf "%s" $QUERY_STRING | awk 'BEGIN{RS="&"}{print}' | mail -s 'CTF registration' neale@woozle.org
TITLE='Team registered'
cat <<EOD
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>$TITLE</title>
    <meta name="viewport" content="width=device-width" />
    <link rel="stylesheet" href="/dirtbags.css" type="text/css" />
    <link rel="icon" type="image/png" href="/icon.png" />
  </head>
  <body>
    <h1>$TITLE</h1>
EOD
echo '<p>Your team registration has been sent to the event organizer.'
echo 'You should get an email back in the next day or two.</p>'
echo '<p>See you at the event!</p>'
cat <<EOD
    <div id="navigation">
      <ul>
        <li><a href="/">Home</a></li>
        <li><a href="/py-pcap.html">py-pcap</a></li>
        <li><a href="/tools/">Tools</a></li>
        <li><a href="/g.cgi">VCS</a></li>
      </ul>
    </div>
  </body>
</html>
EOD
