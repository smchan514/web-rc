#pragma once

/**
 * Prototype HTML page for the remote control
 */
const char * WEB_CONTENT_INDEX_HTML = R"HTML(
<html>

<head>
  <link rel="stylesheet" type="text/css" href="mystyle.css">
</head>

<body>
  <table>
    <tr>
      <td><button id="ajaxButtonTVPOWER" type="button" class="power">TV</button></td>
      <td></td>
      <td><button id="ajaxButtonDVRPOWER" type="button" class="power">DVR</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonGUIDE" type="button">GUIDE</button></td>
      <td></td>
      <td><button id="ajaxButtonINFO" type="button">INFO</button></td>
    </tr>
    <tr>
      <td></td>
      <td><button id="ajaxButtonUP" type="button">&uarr;</button></td>
      <td></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonLEFT" type="button">&larr;</button></td>
      <td><button id="ajaxButtonSELECT" type="button">OK</button></td>
      <td><button id="ajaxButtonRIGHT" type="button">&rarr;</button></td>
    </tr>
    <tr>
      <td></td>
      <td><button id="ajaxButtonDOWN" type="button">&darr;</button></td>
      <td></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonLAST" type="button">LAST</button></td>
      <td></td>
      <td><button id="ajaxButtonEXIT" type="button">EXIT</button></td>
    </tr>
    <tr>
      <td colspan="3">
        <table width="100%">
          <tr>
            <td><button id="ajaxButtonA" type="button" class="A">A</button></td>
            <td><button id="ajaxButtonB" type="button" class="B">B</button></td>
            <td><button id="ajaxButtonC" type="button" class="C">C</button></td>
            <td><button id="ajaxButtonD" type="button" class="D">D</button></td>
          </tr>
        </table>
      </td>
    </tr>
    <tr>
      <td><button id="ajaxButtonVOLUMEUP" type="button">+</button></td>
      <td><button id="ajaxButtonPAGEUP" type="button">&#x21C8;</button></td>
      <td><button id="ajaxButtonCHANNELUP" type="button">+</button></td>
    </tr>
    <tr>
      <td>Vol</td>
      <td>Pages</td>
      <td>CH</td>
    </tr>
    <tr>
      <td><button id="ajaxButtonVOLUMEDOWN" type="button">-</button></td>
      <td><button id="ajaxButtonPAGEDOWN" type="button">&#x21CA;</button></td>
      <td><button id="ajaxButtonCHANNELDOWN" type="button">-</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonMUTE" type="button">Mute</button></td>
      <td></td>
      <td><button id="ajaxButtonLIVE" type="button">LIVE</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonREW8SECS" type="button">&#x21B6;</button></td>
      <td><button id="ajaxButtonLIST" type="button">LIST</button></td>
      <td><button id="ajaxButtonFFW8SECS" type="button">&#x21B7;</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonREW" type="button">&lt;&lt;</button></td>
      <td><button id="ajaxButtonPAUSE" type="button">||</button></td>
      <td><button id="ajaxButtonFFW" type="button">&gt;&gt;</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonSTOP" type="button">STOP</button></td>
      <td><button id="ajaxButtonPLAY" type="button">PLAY</button></td>
      <td><button id="ajaxButtonRECORD" type="button">REC</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButton1" type="button">1</button></td>
      <td><button id="ajaxButton2" type="button">2</button></td>
      <td><button id="ajaxButton3" type="button">3</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButton4" type="button">4</button></td>
      <td><button id="ajaxButton5" type="button">5</button></td>
      <td><button id="ajaxButton6" type="button">6</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButton7" type="button">7</button></td>
      <td><button id="ajaxButton8" type="button">8</button></td>
      <td><button id="ajaxButton9" type="button">9</button></td>
    </tr>
    <tr>
      <td><button id="ajaxButtonASTERISK" type="button">*</button></td>
      <td><button id="ajaxButton0" type="button">0</button></td>
      <td><button id="ajaxButtonPOUND" type="button">#</button></td>
    </tr>
  </table>
  <hr/>
  <table>
    <tr>
      <td>Meteomedia</td>
      <td><button id="ajaxButtonMETEOMEDIA" type="button">621</button></td>
    </tr>
    <tr>
      <td>TSN1</td>
      <td><button id="ajaxButtonTSN1" type="button">786</button></td>
    </tr>
    <tr>
      <td>CTV</td>
      <td><button id="ajaxButtonCTV" type="button">607</button></td>
    </tr>
    <tr>
      <td>CBS</td>
      <td><button id="ajaxButtonCBS" type="button">687</button></td>
    </tr>
    <tr>
      <td>CBC</td>
      <td><button id="ajaxButtonCBC" type="button">606</button></td>
    </tr>
    <tr>
      <td>SRC</td>
      <td><button id="ajaxButtonSRC" type="button">602</button></td>
    </tr>
  </table>

  <script>
    (() => {
      document.getElementById("ajaxButtonTVPOWER").onclick = () => { sendSony('#A90'); };
      document.getElementById("ajaxButtonVOLUMEUP").onclick = () => { sendSony('#490'); };
      document.getElementById("ajaxButtonVOLUMEDOWN").onclick = () => { sendSony('#C90'); };
      document.getElementById("ajaxButtonMUTE").onclick = () => { sendSony('#290'); };

      document.getElementById("ajaxButtonDVRPOWER").onclick = () => { sendPanasonicOld('#37C107'); };
      document.getElementById("ajaxButtonLIST").onclick = () => { sendPanasonicOld('#36C926'); };
      document.getElementById("ajaxButtonSELECT").onclick = () => { sendPanasonicOld('#366133'); };
      document.getElementById("ajaxButtonUP").onclick = () => { sendPanasonicOld('#36812F'); };
      document.getElementById("ajaxButtonDOWN").onclick = () => { sendPanasonicOld('#37A10B'); };
      document.getElementById("ajaxButtonLEFT").onclick = () => { sendPanasonicOld('#37810F'); };
      document.getElementById("ajaxButtonRIGHT").onclick = () => { sendPanasonicOld('#364137'); };
      document.getElementById("ajaxButtonGUIDE").onclick = () => { sendPanasonicOld('#36C127'); };
      document.getElementById("ajaxButtonINFO").onclick = () => { sendPanasonicOld('#36213B'); };
      document.getElementById("ajaxButtonLAST").onclick = () => { sendPanasonicOld('#36E123'); };
      document.getElementById("ajaxButtonEXIT").onclick = () => { sendPanasonicOld('#366932'); };
      document.getElementById("ajaxButtonREW8SECS").onclick = () => { sendPanasonicOld('#37C906'); };
      document.getElementById("ajaxButtonFFW8SECS").onclick = () => { sendPanasonicOld('#37B109'); };
      document.getElementById("ajaxButtonLIVE").onclick = () => { sendPanasonicOld('#36B129'); };
      document.getElementById("ajaxButtonA").onclick = () => { sendPanasonicOld('#37E902'); };
      document.getElementById("ajaxButtonB").onclick = () => { sendPanasonicOld('#36193C'); };
      document.getElementById("ajaxButtonC").onclick = () => { sendPanasonicOld('#37191C'); };
      document.getElementById("ajaxButtonD").onclick = () => { sendPanasonicOld('#0F7E10'); };
      document.getElementById("ajaxButtonPAGEUP").onclick = () => { sendPanasonicOld('#36D924'); };
      document.getElementById("ajaxButtonPAGEDOWN").onclick = () => { sendPanasonicOld('#37D904'); };
      document.getElementById("ajaxButtonREW").onclick = () => { sendPanasonicOld('#37291A'); };
      document.getElementById("ajaxButtonFFW").onclick = () => { sendPanasonicOld('#36293A'); };
      document.getElementById("ajaxButtonPLAY").onclick = () => { sendPanasonicOld('#37990C'); };
      document.getElementById("ajaxButtonPAUSE").onclick = () => { sendPanasonicOld('#374117'); };
      document.getElementById("ajaxButtonRECORD").onclick = () => { sendPanasonicOld('#375914'); };
      document.getElementById("ajaxButtonSTOP").onclick = () => { sendPanasonicOld('#365934'); };
      document.getElementById("ajaxButton1").onclick = () => { sendPanasonicOld('#36113D'); };
      document.getElementById("ajaxButton2").onclick = () => { sendPanasonicOld('#37111D'); };
      document.getElementById("ajaxButton3").onclick = () => { sendPanasonicOld('#36912D'); };
      document.getElementById("ajaxButton4").onclick = () => { sendPanasonicOld('#37910D'); };
      document.getElementById("ajaxButton5").onclick = () => { sendPanasonicOld('#365135'); };
      document.getElementById("ajaxButton6").onclick = () => { sendPanasonicOld('#375115'); };
      document.getElementById("ajaxButton7").onclick = () => { sendPanasonicOld('#36D125'); };
      document.getElementById("ajaxButton8").onclick = () => { sendPanasonicOld('#37D105'); };
      document.getElementById("ajaxButton9").onclick = () => { sendPanasonicOld('#363139'); };
      document.getElementById("ajaxButton0").onclick = () => { sendPanasonicOld('#373119'); };
      document.getElementById("ajaxButtonASTERISK").onclick = () => { sendPanasonicOld('#37E103'); };
      document.getElementById("ajaxButtonPOUND").onclick = () => { sendPanasonicOld('#36B928'); };
      document.getElementById("ajaxButtonCHANNELUP").onclick = () => { sendPanasonicOld('#377111'); };
      document.getElementById("ajaxButtonCHANNELDOWN").onclick = () => { sendPanasonicOld('#36F121'); };

      document.getElementById("ajaxButtonMETEOMEDIA").onclick = () => { sendChannel(621); };
      document.getElementById("ajaxButtonCBS").onclick = () => { sendChannel(687); };
      document.getElementById("ajaxButtonTSN1").onclick = () => { sendChannel(786); };
      document.getElementById("ajaxButtonCTV").onclick = () => { sendChannel(607); };
      document.getElementById("ajaxButtonCBC").onclick = () => { sendChannel(606); };
      document.getElementById("ajaxButtonSRC").onclick = () => { sendChannel(602); };

      function sendChannel(channelNumber) {
        const NUMKEYS = ['#373119', '#36113D', '#37111D', '#36912D', '#37910D', '#365135', '#375115', '#36D125', '#37D105', '#363139'];
        let httpRequest = new XMLHttpRequest();

        if (!httpRequest) {
          alert('Giving up :( Cannot create an XMLHTTP instance');
          return false;
        }

        let irCodeSequence = "";
        channelNumber = Math.abs(channelNumber);
        while(channelNumber > 0)
        {
          if(irCodeSequence.length > 0)
          {
            irCodeSequence = " " + irCodeSequence;
          }

          // Prepend IR code corresponding to the last digit
          let lastDigit = Math.trunc(channelNumber % 10);
          irCodeSequence = NUMKEYS[lastDigit] + irCodeSequence;
          channelNumber = Math.trunc(channelNumber / 10);
        }

        httpRequest.onreadystatechange = (event) => { alertContents(event); };
        httpRequest.open('POST', 'send_panasonic_old?ir_code=' + encodeURIComponent(irCodeSequence));
        httpRequest.send();
      }

      function sendPanasonicOld(irCode) {
        let httpRequest = new XMLHttpRequest();

        if (!httpRequest) {
          alert('Giving up :( Cannot create an XMLHTTP instance');
          return false;
        }
        httpRequest.onreadystatechange = (event) => { alertContents(event); };
        httpRequest.open('POST', 'send_panasonic_old?ir_code=' + encodeURIComponent(irCode));
        httpRequest.send();
      }

      function sendSony(irCode) {
        let httpRequest = new XMLHttpRequest();

        if (!httpRequest) {
          alert('Giving up :( Cannot create an XMLHTTP instance');
          return false;
        }
        httpRequest.onreadystatechange = (event) => { alertContents(event); };
        httpRequest.open('POST', 'send_sony?ir_code=' + encodeURIComponent(irCode));
        httpRequest.send();
      }

      function alertContents(event) {
        let httpRequest = event.target;
        if (httpRequest.readyState === XMLHttpRequest.DONE) {
          if (httpRequest.status === 200) {
            //alert(httpRequest.responseText);
            console.log('Success');
          } else {
            alert('There was a problem with the request.');
          }
        }
      }
    })();
  </script>

</body>
</html>
)HTML";

const char * WEB_CONTENT_MYSTYLE_CSS = R"HTML(
body {
    background-color: black;
}

table {
    background-color: lightgray;
}

td {
    text-align: center;
    width: 8em;
    padding: 0.3em;
    font-family: monospace;
    font-size: 2em;
}

button {
    font-family: monospace;
    font-size: 2em;
    color: black;
    width: 100%;
    height: 1.5em;
}

button.power {
    color: white;
    background-color: black;
}

button.A {
    background-color: yellow;
}
button.B {
    background-color: lightskyblue;
}
button.C {
    background-color: red;
}
button.D {
    background-color: green;
}
)HTML";
