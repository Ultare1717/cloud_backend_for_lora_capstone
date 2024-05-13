#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char html_content[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset=utf-8>
    <title>Gateway Web Server</title>
    <meta content="width=device-width, initial-scale=1" name=viewport>
    <style>
      html {
    font-family: sans-serif;
    }
    
    body {
    padding: 20px;
    background-color: #2b6cb0; /* Brighter blue */
    }
    
    hr {
    padding: 0;
    }
    
    details,
    main,
    summary {
    display: block;
    }
    
    a {
    background-color: transparent;
    }
    
    a:active,
    a:hover {
    outline: 0;
    }
    
    b {
    font-weight: 700;
    }
    
    h1 {
    font-size: 36px;
    margin: 10px 0 5px 0;
    color: #2b6cb0; /* Brighter blue */
    }
    
    h2 {
    font-size: 24px;
    color: #2b6cb0; /* Brighter blue */
    }
    
    input:-webkit-autofill,
    input:-webkit-autofill:hover,
    input:-webkit-autofill:focus,
    input:-webkit-autofill:active {
    -webkit-box-shadow: 0 0 0 30px #fff inset!important;
    }
    
    input[type='checkbox'] {
    box-sizing: border-box;
    padding: 0;
    }
    
    input[type='text'],
    input[type='number'],
    input[type='password'],
    select {
    height: 40px;
    width: 90%;
    padding: 0 0 0 20px;
    border: 1px solid #ccc;
    border-radius: 6px;
    font-size: 16px;
    background-color: #fff; /* White background */
    }
    
    input[type=file] {
    display: none;
    }
    
    input::placeholder {
    color: #5e5e5e;
    }
    
    input:hover {
    border-color: rgba(0, 0, 0, 0.8);
    box-shadow: 0 1px 4px 0 rgba(220, 220, 229, 0.9);
    }
    
    input:focus,
    select:focus {
    border-color: #3898ec;
    outline: 0;
    }
    
    input[type=number]:hover::-webkit-inner-spin-button {
    -webkit-appearance: none;
    -moz-appearance: textfield;
    }
    
    footer {
    text-align: center;
    font-size: 12px;
    margin: 40px;
    }
    
    button,
    .btn {
    display: inline-flex;
    padding: 10px 15px;
    background-color: #2E8BC0; /* Brighter blue */
    color: #fff;
    border: 0;
    cursor: pointer;
    min-width: 40%;
    border-radius: 5px;
    justify-content: center;
    }
    
    button:hover,
    .btn:hover {
    filter: brightness(85%);
    }
    
    ul {
    display: table;
    text-align: left;
    margin: 0 auto 10px auto;
    }
    
    hr {
    width: 100%;
    order: 997;
    }
    
    select {
    width: 92.5%;
    }
    
    .input-label {
    align-self: self-start;
    color: #015293;
    position: relative;
    left: 5%;
    bottom: -5px;
    border-radius: 6px;
    border: 1px solid #ccc;
    background-color: #fff;
    font-size: 13.5px;
    padding: 2px 10px 0 10px;
    }
    
    .input-label:hover {
    border-color: rgba(0, 0, 0, 0.8);
    }
    
    .esp-info {
    text-align: center;
    margin-bottom: 12px;
    }
    
    .row-wrapper {
    display: flex;
    flex-wrap: nowrap;
    align-items: baseline;
    gap: 20px;
    }
    
    .loading {
    color: #ffffff9e;
    text-align: center;
    }
    
    .loader {
    position: relative;
    height: auto;
    overflow: hidden;
    }
    
    .spinH {
    top: 50%;
    position: absolute;
    height: 8px;
    width: 8px;
    background: #ffffff2b;
    border-radius: 100%;
    }
    
    .spin-1H {
    animation: spinnerH 3s infinite linear;
    }
    
    .spin-2H {
    animation: spinnerH 3s 0.1s infinite linear;
    }
    
    .spin-3H {
    animation: spinnerH 3s 0.2s infinite linear;
    }
    
    .spin-4H {
    animation: spinnerH 3s 0.3s infinite linear;
    }
    
    @keyframes spinnerH {
    0% {
    transform: translateX(0)
    }
    20% {
    transform: translate(200px)
    }
    70% {
    transform: translateX(505px)
    }
    100% {
    transform: translateX(800px)
    }
    }
    
    .progress-wrap {
    text-align: center;
    position: relative;
    width: 60%;
    height: 25px;
    margin: 20px auto;
    background: #9e9e9e7d;
    font-size: 20px;
    transition: all 0.4s ease;
    }
    
    .progress-wrap:not(.active) {
    cursor: pointer;
    background: #9e9e9e00;
    }
    
    .progress-wrap .progress {
    width: 0;
    z-index: 5;
    background: #9e9e9ea1;
    opacity: 0;
    transition: all 0.3s ease;
    }
    
    .progress-wrap.active .progress {
    opacity: 1;
    animation: progress-anim 10s ease 0s;
    }
    
    .progress-wrap[data-progress-style='fill-back'] .progress {
    position: absolute;
    left: 0;
    top: 0;
    right: 0;
    bottom: 0;
    }
    
    .d-modal {
    width: 70%;
    border-radius: 10px;
    border-style: solid;
    border-width: 1px;
    border-color: #3333336e;
    background-color: hsl(199.53deg 18.3% 46.08% / 90%);
    box-shadow: rgba(0, 0, 0, 0.24) 0 3px 8px;
    left: 50%;
    position: absolute;
    top: 50%;
    transform: translate(-50%, -50%);
    flex-direction: column;
    }
    
    .d-modal-title {
    color: #111827;
    padding: 1.5em;
    position: relative;
    width: calc(100% - 4.5em);
    }
    
    .d-modal-content {
    border-top: 1px solid #e0e0e0;
    padding: 1.5em;
    overflow: auto;
    }
    
    .topnav {
    background-color: #333;
    overflow: hidden;
    width: fit-content;
    float: right;
    border-radius: 5px;
    align-self: flex-end;
    bottom: 5px;
    right: 20px;
    }
    
    .topnav a {
    float: left;
    display: block;
    color: #f2f2f2;
    text-align: center;
    padding: 5px 10px;
    text-decoration: none;
    font-size: 16px;
    }
    
    .topnav a:hover {
    filter: brightness(55%);
    cursor: pointer;
    }
    
    .topnav a.active {
    background-color: #56c080;
    color: white;
    }
    
    .topnav .icon {
    display: none;
    }
    
    .logo {
    width: 100%;
    }
    
    .lbl-wifi {
    align-self: flex-end;
    }
    
    .table {
    width: 90%;
    margin: auto;
    border-collapse: collapse;
    border-spacing: 0;
    }
    
    .svg {
    display: flex;
    width: 20px;
    margin-right: 10px;
    }
    
    .svg-e {
    margin-top: 5px;
    }
    
    .svg-es {
    margin-top: 30px;
    }
    
    .output {
    color: white;
    }
    
    .form {
    padding: 10px 0;
    width: 85%;
    text-align: center;
    }
    
    .ctn:before,
    .ctn:after {
    content: " ";
    display: table;
    grid-column-start: 1;
    grid-row-start: 1;
    grid-column-end: 2;
    grid-row-end: 2;
    }
    
    .ctn:after {
    clear: both;
    }
    
    .ctn {
    display: flex;
    flex-direction: column;
    position: relative;
    overflow: visible;
    max-width: 960px;
    margin: 0 auto 10px auto;
    padding: 10px 40px;
    border-radius: 10px;
    border: 1px solid;
    background-color: hsla(0, 0%, 100%, 0.7);
    box-shadow: rgba(0, 0, 0, 0.24) 0 3px 8px;
    }
    
    .btn-bar {
    display: flex;
    padding: 20px;
    justify-content: center;
    flex-wrap: wrap;
    grid-column-gap: 30px;
    grid-row-gap: 20px;
    order: 998;
    }
    
    .tf-wrapper {
    display: flex;
    margin-bottom: 10px;
    flex-direction: column;
    align-items: center;
    }
    
    .title {
    display: flex;
    }
    
    .heading {
    width: 100%;
    text-align: right;
    margin-right: 0;
    }
    
    .heading-2 {
    font-weight: 400;
    text-align: center;
    margin: 10px auto;
    color: #0d4869; /* Darker blue */
    }
    
    .toggle {
    cursor: pointer;
    display: block;
    padding: 4px;
    width: fit-content;
    margin: 0 0 18px -10px;
    }
    
    .toggle-label {
    margin: 0 20px 0 20px;
    position: relative;
    top: 2px;
    }
    
    .toggle-switch {
    display: inline-block;
    background: #ccc;
    border-radius: 16px;
    width: 58px;
    height: 32px;
    position: relative;
    vertical-align: middle;
    transition: background .25s;
    }
    
    .toggle-switch:before,
    .toggle-switch:after {
    content: "";
    }
    
    .toggle-switch:before {
    display: block;
    background: linear-gradient(to bottom, #fff 0%, #eee 100%);
    border-radius: 50%;
    box-shadow: 0 0 0 1px rgba(0, 0, 0, 0.25);
    width: 24px;
    height: 24px;
    position: absolute;
    top: 4px;
    left: 4px;
    transition: left .25s;
    }
    
    .toggle:hover .toggle-switch:before {
    background: linear-gradient(to bottom, #fff 0%, #fff 100%);
    box-shadow: 0 0 0 1px rgba(0, 0, 0, 0.5);
    }
    
    .t-check:checked+.toggle-switch {
    background: #56c080; /* Brighter green */
    }
    
    .t-check:checked+.toggle-switch:before {
    left: 30px;
    }
    
    .t-check {
    position: absolute;
    visibility: hidden;
    }
    
    .pswd {
    display: flex;
    flex-direction: row;
    align-items: center;
    width: 100%;
    justify-content: center;
    }
    
    .show-hide-wrap {
    position: absolute;
    right: 8%;
    cursor: pointer;
    }
    
    .firmware {
    display: flex;
    flex-direction: column;
    align-items: center;
    }
    
    .fw-upload {
    display: inline-block;
    padding: 12px 20px;
    cursor: pointer;
    border-radius: 5px;
    margin-bottom: 20px;
    background: dimgray;
    color: #fff;
    }
    
    .fw-upload:hover {
    filter: brightness(85%);
    }
    
    .btn,
    .submit {
    min-width: 25%;
    }
    
    #about {
    color: lightgray;
    }
    
    #esp-ip {
    display: inline-block;
    margin-bottom: 5px;
    }
    
    @media screen and (max-width: 991px) {
    .wifi-connect {
    padding-right: 20px;
    padding-left: 20px;
    }
    }
    
    @media screen and (max-width: 767px) {
    .wifi-connect {
    padding-right: 10px;
    padding-left: 10px;
    }
    select {
    width: 93.5%;
    }
    }
    
    @media screen and (max-width: 608px) {
    h1 {
    font-size: 24px;
    color: #2b6cb0; /* Brighter blue */
    }
    .btn-bar {
    margin-top: 20px;
    flex-direction: column;
    }
    .topnav {
    margin-bottom: 5px;
    width: 55%;
    }
    .topnav a {
    padding: 5px 20px;
    }
    .topnav a:not(.active) {
    display: none;
    }
    .topnav a.icon {
    float: right;
    display: block;
    }
    .topnav.responsive .icon {
    position: absolute;
    right: 0;
    top: 0;
    }
    .topnav.responsive a {
    float: none;
    display: block;
    text-align: left;
    }
    .hide-tiny {
    display: none;
    }
    .toggle-label {
    margin: 0 5px 0 5px;
    }
    .show-hide-wrap {
    right: 4%;
    }
    }
    
    @media screen and (max-width: 479px) {
    body {
    padding: 2px;
    }
    select {
    width: 95.5%;
    }
    .heading-2 {
    margin-top: 10px;
    padding: 0;
    }
    .form {
    padding: 0;
    }
    .ctn {
    max-width: 100%;
    padding: 0 10px 0 10px;
    }
    .row-wrapper {
    flex-direction: column;
    gap: 0;
    }
    }
    
    .hide {
    display: none;
    }

    .terminal-box {
    background-color: #000;
    border: 1px solid #999;
    border-radius: 5px;
    padding: 10px;
    margin-bottom: 20px;
    overflow: auto;
}

.terminal-box h3 {
    color: #fff;
    margin-top: 0;
}

.terminal-content {
    font-family: monospace;
    color: #fff;
    margin-top: 10px;
}


.terminal-content div {
    color: #fff; /* Change text color */
}


    
    
    
    </style>
</head>
<body>
    <main id=main-box>
        <header class="ctn">
            <div class=title>
                <div id=img-logo title='Click to upload your logo file'></div>
                <div class=heading>
                  <h1 id=name-logo>Gateway Web Server</h1>
                  <span id=esp-ip></span><br>
                </div>
            </div>
            <!-- <div class=topnav id=top-nav>
                <span id="nav-link"><a id=set-wifi class="a-link active" data-box="wifi-box">Setup</a></span>
                <a class="a-link icon" id=hum-btn>
                    <div class=svg style=margin:-2px >
                        <svg id=svg-menu height="16pt" fill=currentColor viewBox="0 0 20 18"></svg>
                    </div>
                </a>
            </div> -->
        </header>
        <div id=wifi-box-uninitialized class="ctn opt-box">
            <h2 class=heading-2>Gateway Initialization</h2>
            <div id=wifi>
                <div class="tf-wrapper">
                    <label class="input-label toggle">
                      <input id=enterprise-wifi-toggle type=checkbox class="t-check">
                      <div class=toggle-switch></div>
                      <span class=toggle-label>Enterprise Wifi</span>
                    </label>
                  </div>
                <div class=tf-wrapper>
                    <label for=ssid class=input-label>SSID</label>
                    <input type=text placeholder="Enter your WiFI SSID name" id="ssid">
                </div>
                <div class=hide id=conf-wifi> 
                    <div class="tf-wrapper">
                        <label for=enterprise-username class=input-label>Enterprise Username</label>
                        <input type=text placeholder="Enter your Enterprise Username" id=enterprise-username >
                    </div>
                </div>
                <div class=tf-wrapper>
                    <label for=password class=input-label>Password</label>
                    <div class=pswd>
                      <input type=password placeholder="Enter your WiFi password"
                        id=password >
                      <span class=show-hide-wrap id=show-hide-password>
                        <a class="show-hide hide" id=show-pass>
                            <div class=svg><svg class=svg-e id=svg-eye viewBox="0 0 24 24"></svg></div>
                        </a>
                        <a class="show-hide" id=hide-pass>
                            <div class=svg><svg class=svg-e id=svg-no-eye viewBox="0 0 24 24"></svg></div>
                        </a>
                      </span>  
                    </div>
                </div> 
            </div>
            <hr>
            <div class="btn-bar ">
                <a id=connect-wifi class="btn">
                    <div class=svg><svg id=svg-connect fill=currentColor viewBox="0 0 24 24"></svg></div>
                    <span>Connect</span>
                </a>
            </div>
        </div>

        <div id=wifi-box-initialized class="ctn opt-box hide">
            <h2 class=heading-2>Gateway Provisioning</h2>
            <div id="connected-wifi-info">
                <p>Connected to: <span id="connected-ssid"></span></p>
                <div class=tf-wrapper>
                    <label for=system class=input-label>System Name</label>
                    <input type=text placeholder="Enter your System Name" id="system">
                </div>
                <div class=tf-wrapper>
                    <label for=access-key class=input-label>Access Key</label>
                    <input type=text placeholder="Enter your Access Key" id="access-key">
                </div>
                <div class=tf-wrapper>
                    <label for=secret-access-key class=input-label>Secret Access Key</label>
                    <input type=password placeholder="Enter your Secret Access Key" id="secret-access-key">
                    <span class=show-hide-wrap id=show-hide-secret-access-key>
                        <a class="show-hide hide" id=show-secret-access-key>
                            <div class=svg><svg class=svg-es id=svg-eye-sak viewBox="0 0 24 24"></svg></div>
                        </a>
                        <a class="show-hide" id=hide-secret-access-key>
                            <div class=svg><svg class=svg-es id=svg-no-eye-sak viewBox="0 0 24 24"></svg></div>
                        </a>
                    </span> 
                </div>
                <div id="additional-fields">
                  <!-- Additional fields will be dynamically added here -->
              </div>
              <div class="btn-bar">
                <button id="add-field-btn" class="btn">
                    <div class="svg">
                        <svg id="svg-add-sensor" fill="currentColor" viewBox="0 0 24 24"></svg>
                    </div>
                    <span>Add Sensor</span>
                </button>
                <button id="remove-field-btn" class="btn">
                    <div class="svg">
                        <svg id="svg-remove-sensor" fill="currentColor" viewBox="0 0 24 24"></svg>
                    </div>
                    <span>Remove Sensor</span>
                </button>
            </div>
            
                <div class="btn-bar ">
                    <a id=connect-aws class="btn">
                        <div class=svg><svg id=svg-connect-aws fill=currentColor viewBox="0 0 24 24"></svg></div>
                        <span>Provision Device</span>
                    </a>
                </div>
            </div>
        </div>

        <div id=aws-box-initialized class="ctn opt-box hide" >
          <h2 class=heading-2>Gateway Provisioned and Connected To AWS</h2>
          <div id="aws-connected-info">
            <div id="gateway-control" class="terminal-box">
              <h3>Gateway Control Information</h3>
              <div class="terminal-content">
                  <div id="control-message"></div>
              </div>
          </div>
          
          </div>
      </div>
      
    </main>
    
    <div class="loader hide" id=loader>
      <div class="loading">Loading...</div>
      <div class="spinH spin-1H"></div>
      <div class="spinH spin-2H"></div>
      <div class="spinH spin-3H"></div>
      <div class="spinH spin-4H"></div>
    </div>
    
    <details id=modal-message>
        <summary></summary>
        <div class=d-modal>
            <div class=d-modal-title><h2 id=message-title>t</h2></div>
            <div class=d-modal-content><p id=message-body></p></div>
            <div class=btn-bar>
                <a id=ok-modal class="btn hide" onclick=closeModal(true)><span>OK</span></a>
                <a id=close-modal class="btn" onclick=closeModal(false)><span>Close</span></a>
            </div>
        </div>
    </details>
    <footer class=foot>
        <hr>
        <a id=about target=_blank rel=noopener></a>
    </footer>
    <script>
      /*jshint esversion: 9 */
      const svgLogo = '<svg version="1.0" xmlns="http://www.w3.org/2000/svg" width="144.000000pt" height="120.000000pt" viewBox="0 0 144.000000 120.000000" preserveAspectRatio="xMidYMid meet"> <g transform="translate(0.000000,120.000000) scale(0.100000,-0.100000)" fill="#000000" stroke="none"> <path d="M602 1186 c-120 -23 -232 -83 -322 -174 -109 -109 -166 -228 -176 -372 -21 -274 177 -541 456 -616 78 -21 222 -23 300 -5 230 54 418 243 465 466 27 128 11 244 -50 374 -46 96 -159 211 -260 263 -128 66 -278 89 -413 64z m243 -41 c195 -41 363 -187 427 -372 33 -98 32 -260 -3 -353 -102 -271 -387 -426 -672 -365 -312 66 -517 377 -442 670 27 104 72 183 150 261 144 143 339 201 540 159z"/> <path d="M432 888 c-8 -8 -12 -60 -12 -169 l0 -158 -52 -3 -53 -3 0 -105 0 -105 47 -3 c39 -3 47 -6 50 -25 2 -18 10 -22 38 -22 29 0 36 4 38 22 l3 23 229 0 229 0 3 -22 c2 -19 9 -23 38 -23 28 0 36 4 38 22 3 19 11 22 50 25 l47 3 0 105 0 105 -52 3 -53 3 0 158 c0 129 -3 161 -15 171 -12 10 -18 10 -30 0 -12 -10 -15 -42 -15 -171 l0 -159 -240 0 -240 0 0 158 c0 149 -5 182 -30 182 -3 0 -11 -5 -18 -12z"/> </g> </svg>'
      const svgLock =  '<svg height="16pt" viewBox="0 0 24 24"><path d="M12,17A2,2 0 0,0 14,15C14,13.89 13.1,13 12,13A2,2 0 0,0 10,15A2,2 0 0,0 12,17M18,8A2,2 0 0,1 20,10V20A2,2 0 0,1 18,22H6A2,2 0 0,1 4,20V10C4,8.89 4.9,8 6,8H7V6A5,5 0 0,1 12,1A5,5 0 0,1 17,6V8H18M12,3A3,3 0 0,0 9,6V8H15V6A3,3 0 0,0 12,3Z" /></svg>';
      const svgUnlock = '<svg height="16pt" viewBox="0 0 24 24"><path d="M18 1C15.24 1 13 3.24 13 6V8H4C2.9 8 2 8.89 2 10V20C2 21.11 2.9 22 4 22H16C17.11 22 18 21.11 18 20V10C18 8.9 17.11 8 16 8H15V6C15 4.34 16.34 3 18 3C19.66 3 21 4.34 21 6V8H23V6C23 3.24 20.76 1 18 1M10 13C11.1 13 12 13.89 12 15C12 16.11 11.11 17 10 17C8.9 17 8 16.11 8 15C8 13.9 8.9 13 10 13Z" /></svg>';
      const svgScan = '<path d="M12 20L8.4 15.2C9.4 14.45 10.65 14 12 14S14.6 14.45 15.6 15.2L12 20M4.8 10.4L6.6 12.8C8.1 11.67 9.97 11 12 11S15.9 11.67 17.4 12.8L19.2 10.4C17.19 8.89 14.7 8 12 8S6.81 8.89 4.8 10.4M12 2C7.95 2 4.21 3.34 1.2 5.6L3 8C5.5 6.12 8.62 5 12 5S18.5 6.12 21 8L22.8 5.6C19.79 3.34 16.05 2 12 2M7 24H9V22H7V24M15 24H17V22H15V24M11 24H13V22H11V24Z" />';
      const svgConnect = '<path d="M12,21L15.6,16.2C14.6,15.45 13.35,15 12,15C10.65,15 9.4,15.45 8.4,16.2L12,21M12,3C7.95,3 4.21,4.34 1.2,6.6L3,9C5.5,7.12 8.62,6 12,6C15.38,6 18.5,7.12 21,9L22.8,6.6C19.79,4.34 16.05,3 12,3M12,9C9.3,9 6.81,9.89 4.8,11.4L6.6,13.8C8.1,12.67 9.97,12 12,12C14.03,12 15.9,12.67 17.4,13.8L19.2,11.4C17.19,9.89 14.7,9 12,9Z" />';
      const svgSave = '<path d="M15,9H5V5H15M12,19A3,3 0 0,1 9,16A3,3 0 0,1 12,13A3,3 0 0,1 15,16A3,3 0 0,1 12,19M17,3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V7L17,3Z" />';
      const svgRestart = '<path d="M12,4C14.1,4 16.1,4.8 17.6,6.3C20.7,9.4 20.7,14.5 17.6,17.6C15.8,19.5 13.3,20.2 10.9,19.9L11.4,17.9C13.1,18.1 14.9,17.5 16.2,16.2C18.5,13.9 18.5,10.1 16.2,7.7C15.1,6.6 13.5,6 12,6V10.6L7,5.6L12,0.6V4M6.3,17.6C3.7,15 3.3,11 5.1,7.9L6.6,9.4C5.5,11.6 5.9,14.4 7.8,16.2C8.3,16.7 8.9,17.1 9.6,17.4L9,19.4C8,19 7.1,18.4 6.3,17.6Z" />';
      const svgEye = '<path d="M12,9A3,3 0 0,1 15,12A3,3 0 0,1 12,15A3,3 0 0,1 9,12A3,3 0 0,1 12,9M12,4.5C17,4.5 21.27,7.61 23,12C21.27,16.39 17,19.5 12,19.5C7,19.5 2.73,16.39 1,12C2.73,7.61 7,4.5 12,4.5M3.18,12C4.83,15.36 8.24,17.5 12,17.5C15.76,17.5 19.17,15.36 20.82,12C19.17,8.64 15.76,6.5 12,6.5C8.24,6.5 4.83,8.64 3.18,12Z" />';
      const svgNoEye = '<path d="M0 0h24v24H0V0z" fill="none"/><path d="M12 4.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5zM12 17c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z"/>';
      const svgMenu = '<path d="M3,6H21V8H3V6M3,11H21V13H3V11M3,16H21V18H3V16Z"/>';
      
      var closeCb = function(){};
      var port = location.port || (window.location.protocol === 'https:' ? '443' : '80');
      var esp = `${window.location.protocol}//${window.location.hostname}:${port}/`;
      var options = {};
      var configFile;
      var lastBox;
      
      // Element selector shorthands
      var $ = function(el) {
        return document.getElementById(el);
      };
      
      function hide(id) {
        $(id).classList.add('hide');
      }
      
      function show(id) {
        $(id).classList.remove('hide');
      }
      
      function openModal(title, msg, fn, args) {
          $('message-title').innerHTML = title;
          $('message-body').innerHTML = msg;
          $('modal-message').open = true;
          $('main-box').style.filter = "blur(3px)";
          if (typeof fn != 'undefined') {
            closeCb = fn;
            show('ok-modal');
          }
          else
            hide('ok-modal');
        }
      
        function closeModal(do_cb) {
          $('modal-message').open = false;
          $('main-box').style.filter = "";
          if (typeof closeCb != 'undefined' && do_cb)
            closeCb();
        }
      
      function showHidePassword() {
          var inp = $("password");
          if (inp.type === "password") {
            inp.type = "text";
            show('show-pass');
            hide('hide-pass');
          }
          else {
            inp.type = "password";
            hide('show-pass');
            show('hide-pass');
          }
      }
      
      // Function to handle successful WiFi connection
      function handleWifiConnection(ssid) {
          // Hide uninitialized WiFi box and show initialized WiFi box
          $('wifi-box-uninitialized').classList.add('hide');
          $('wifi-box-initialized').classList.remove('hide');
          $('loader').classList.add('hide');
          $('main-box').classList.remove('hide');
      
          // Show connected SSID
          $('connected-ssid').textContent = ssid;
      }
      
      function handleAWSConnection() {
          // Hide uninitialized WiFi box and show initialized WiFi box
          $('aws-box-initialized').classList.remove('hide');
          $('wifi-box-initialized').classList.add('hide');
          $('loader').classList.add('hide');
          $('main-box').classList.remove('hide');
      }
      
      function showLoading() {
        $('loader').classList.remove('hide');
        $('main-box').classList.add('hide');
      }
      
      // Function to reset the form fields and show the form again
      function resetForm() {
        $('loader').classList.add('hide');
        $('main-box').classList.remove('hide');
        $('ssid').value = '';
        $('password').value = '';
        $('enterprise-username').value = '';
        $('enterprise-wifi-toggle').checked = false;
        hide('conf-wifi');
      }
      
      function doConnection() {
          showLoading(); // Show loading spinner
      
          var ssid = $('ssid').value.trim();
          var password = $('password').value.trim();
          var enterpriseWifi = $('enterprise-wifi-toggle').checked;
          var enterpriseUsername = $('enterprise-username').value.trim();
      
          // Input validation
          if (ssid === '') {
              openModal('Connect to WiFi', 'Please enter SSID.');
              resetForm();
              return;
          }
      
          if (password === '') {
              openModal('Connect to WiFi', 'Please enter password.');
              resetForm();
              return;
          }
      
          if (enterpriseWifi && enterpriseUsername === '') {
              openModal('Connect to WiFi', 'Please enter enterprise username.');
              resetForm();
              return;
          }
      
          // Prepare data based on connection type
          var formData = new FormData();
          formData.append('ssid', ssid);
          formData.append('password', password);
          formData.append('is_enterprise', enterpriseWifi);
          if (enterpriseWifi) {
              formData.append('enterprise_username', enterpriseUsername);
          }
      
          // Send the PUT request to connect to WiFi
          fetch('/connect', {
              method: 'PUT',
              body: formData
          })
          .then(response => {
              if (!response.ok) {
                  throw new Error('Failed to connect to WiFi.');
              }
              // After successful connection, start checking WiFi status
              checkWifiConnection(3, 60000, ssid); // Check WiFi status 3 times with a timeout of 30 seconds
          })
          .catch(error => {
              // Handle any errors during fetch or processing
              openModal('Error', error.message);
              resetForm();
          });
      }
      
      function checkWifiConnection(attempts, timeout, ssid) {
          // Keep track of the number of attempts
          var currentAttempt = 0;
          var timeoutOccurred = false;
          var connected = false; // Flag to track successful connection
      
          function check() {
              currentAttempt++;
      
              // If already connected, no need to continue checking
              if (connected) return;
      
              // Send a GET request to check WiFi status
              fetch('/wifi-status')
              .then(response => {
                  if (!response.ok) {
                      throw new Error('Failed to check WiFi status.');
                  }
                  return response.text();
              })
              .then(data => {
                  // Handle the response as needed
                  console.log('WiFi Status:', data);
                  
                  // Check if the response indicates successful WiFi connection
                  if (data === 'WiFi connected successfully!') {
                      // Handle successful WiFi connection
                      console.log('WiFi connected successfully!');
                      openModal('Success', 'WiFi connected successfully!');
                      handleWifiConnection(ssid);
                      connected = true; // Set connected flag
                      return;
                  }
              })
              .catch(error => {
                  // Handle any errors during fetch or processing
                  console.error('Error checking WiFi status:', error.message);
              })
              .finally(() => {
                  if (!connected && currentAttempt < attempts && !timeoutOccurred) {
                      // If attempts are not exhausted and timeout hasn't occurred, schedule the next check
                      setTimeout(check, 20000); // 10 seconds
                  } else {
                      // If attempts are exhausted or timeout occurred, display an error message
                      if (timeoutOccurred) {
                          console.error('Timeout while checking WiFi connection.');
                          openModal('Error', 'Timeout while checking WiFi connection.');
                      } else if (!connected) {
                          console.error('Failed to connect to WiFi after', attempts, 'attempts.');
                          openModal('Error', 'Failed to connect to WiFi after ' + attempts + ' attempts.');
                      }
                      resetForm();
                  }
              });
          }
      
          // Start the first check
          check();
      
          // Set a timeout for the entire function
          setTimeout(() => {
              timeoutOccurred = true;
          }, timeout);
      }
      
      var optionLabels = {
          "Thermocouples": 0,
          "Digital Temperature Sensors": 1,
          "Infrared Temperature Sensors": 2,
          "Capacitive Humidity Sensors": 3,
          "Resistive Humidity Sensors": 4,
          "Thermal Conductivity Humidity Sensors": 5,
          "Gravimetric Humidity Sensors": 6,
          "Soil Moisture Sensors": 7,
          "Capacitive Moisture Sensors": 8,
          "Resistive Moisture Sensors": 9,
          "Optical Moisture Sensors": 10,
          "Photodiodes": 11,
          "Phototransistors": 12,
          "Light-Dependent Resistors (LDRs)": 13,
          "Photovoltaic Cells": 14,
          "Ambient Light Sensors": 15,
          "Passive Infrared (PIR) Motion Sensors": 16,
          "Ultrasonic Motion Sensors": 17,
          "Microwave Motion Sensors": 18,
          "Accelerometers": 19,
          "Gyroscopes": 20,
          "Inductive Proximity Sensors": 21,
          "Capacitive Proximity Sensors": 22,
          "Ultrasonic Proximity Sensors": 23,
          "Infrared Proximity Sensors": 24,
          "Piezoelectric Pressure Sensors": 25,
          "Strain Gauge Pressure Sensors": 26,
          "Capacitive Pressure Sensors": 27,
          "Resonant Pressure Sensors": 28,
          "Optical Pressure Sensors": 29,
          "Carbon Monoxide (CO) Sensors": 30,
          "Carbon Dioxide (CO2) Sensors": 31,
          "Oxygen (O2) Sensors": 32,
          "Methane (CH4) Sensors": 33,
          "Volatile Organic Compound (VOC) Sensors": 34,
          "Microphones": 35,
          "Sound Level Sensors": 36,
          "Acoustic Wave Sensors": 37,
          "Piezoelectric Sensors": 38,
          "MEMS Microphones": 39,
          "Fingerprint Sensors": 40,
          "Retinal Scanners": 41,
          "Iris Scanners": 42,
          "Heart Rate Sensors": 43,
          "Blood Oxygen Sensors": 44,
          "pH Sensors": 45,
          "Gas Chromatography Sensors": 46,
          "Ion-Selective Electrodes": 47,
          "Electrochemical Sensors": 48,
          "Biosensors": 49,
          "pH Sensors": 50,
          "Dissolved Oxygen Sensors": 51,
          "Turbidity Sensors": 52,
          "Conductivity Sensors": 53,
          "Chlorine Sensors": 54
      };
      
      
      function doProvision() {
          showLoading(); // Show loading spinner
          var systemName = document.getElementById('system').value.trim();
          var accessKey = document.getElementById('access-key').value.trim();
          var secretAccessKey = document.getElementById('secret-access-key').value.trim();
          // Input validation
          if (systemName === '') {
              openModal('Provision Device', 'Please enter System Name.');
              resetProvisionForm();
              return;
          }
      
          if (accessKey === '') {
              openModal('Provision Device', 'Please enter Access Key.');
              resetProvisionForm();
              return;
          }
      
          if (secretAccessKey === '') {
              openModal('Provision Device', 'Please enter Secret Access Key.');
              resetProvisionForm();
              return;
          }
      
          // Check if at least one additional sensor field is added
          var additionalFields = document.getElementById('additional-fields');
          var children = additionalFields.children;
          if (children.length === 0) {
              openModal('Provision Device', 'Please add at least one sensor.');
              resetProvisionForm();
              return;
          }
      
          var optionLabels = {
          "Thermocouples": 0,
          "Digital Temperature Sensors": 1,
          "Infrared Temperature Sensors": 2,
          "Capacitive Humidity Sensors": 3,
          "Resistive Humidity Sensors": 4,
          "Thermal Conductivity Humidity Sensors": 5,
          "Gravimetric Humidity Sensors": 6,
          "Soil Moisture Sensors": 7,
          "Capacitive Moisture Sensors": 8,
          "Resistive Moisture Sensors": 9,
          "Optical Moisture Sensors": 10,
          "Photodiodes": 11,
          "Phototransistors": 12,
          "Light-Dependent Resistors (LDRs)": 13,
          "Photovoltaic Cells": 14,
          "Ambient Light Sensors": 15,
          "Passive Infrared (PIR) Motion Sensors": 16,
          "Ultrasonic Motion Sensors": 17,
          "Microwave Motion Sensors": 18,
          "Accelerometers": 19,
          "Gyroscopes": 20,
          "Inductive Proximity Sensors": 21,
          "Capacitive Proximity Sensors": 22,
          "Ultrasonic Proximity Sensors": 23,
          "Infrared Proximity Sensors": 24,
          "Piezoelectric Pressure Sensors": 25,
          "Strain Gauge Pressure Sensors": 26,
          "Capacitive Pressure Sensors": 27,
          "Resonant Pressure Sensors": 28,
          "Optical Pressure Sensors": 29,
          "Carbon Monoxide (CO) Sensors": 30,
          "Carbon Dioxide (CO2) Sensors": 31,
          "Oxygen (O2) Sensors": 32,
          "Methane (CH4) Sensors": 33,
          "Volatile Organic Compound (VOC) Sensors": 34,
          "Microphones": 35,
          "Sound Level Sensors": 36,
          "Acoustic Wave Sensors": 37,
          "Piezoelectric Sensors": 38,
          "MEMS Microphones": 39,
          "Fingerprint Sensors": 40,
          "Retinal Scanners": 41,
          "Iris Scanners": 42,
          "Heart Rate Sensors": 43,
          "Blood Oxygen Sensors": 44,
          "pH Sensors": 45,
          "Gas Chromatography Sensors": 46,
          "Ion-Selective Electrodes": 47,
          "Electrochemical Sensors": 48,
          "Biosensors": 49,
          "pH Sensors": 50,
          "Dissolved Oxygen Sensors": 51,
          "Turbidity Sensors": 52,
          "Conductivity Sensors": 53,
          "Chlorine Sensors": 54
      };
      
      
          var selectedValues = [];
          for (var i = 0; i < children.length; i++) {
              var select = children[i].querySelector('select'); // Accessing the input element
              var value = select.value; // Getting the input value
              if (selectedValues.includes(value)) {
                  openModal('Provision Device', 'Duplicate sensor selections detected.');
                  resetProvisionForm();
                  return;
              } else {
                  selectedValues.push(value);
              }
          }
      
          // Prepare data including additional sensor fields
          var formData = new FormData();
          formData.append('system_name', systemName);
          formData.append('access_key', accessKey);
          formData.append('secret_access_key', secretAccessKey);
      
          // Append additional sensor fields
          for (var i = 0; i < children.length; i++) {
              formData.append('sensor_' + (i + 1), optionLabels[children[i].querySelector('select').value]);
          }
          formData.append("number_of_sensors", children.length);
          console.log(formData);
      
          //Send initial request to provision the device
          fetch('/provision', {
              method: 'PUT',
              body: formData
          })
          .then(response => {
              if (!response.ok) {
                  throw new Error('Failed to connect to AWS.');
              }
              // After successful connection, start checking AWS provisioning status
              checkAwsProvisioningStatus(); // Check status 3 times with a timeout of 20 seconds
          })
          .catch(error => {
              // Handle any errors during fetch or processing
              openModal('Error', error.message);
              resetProvisionForm();
          });
      }
      
      
      
      function checkAwsProvisioningStatus() {
          // Wait for 20 seconds
          setTimeout(() => {
              sendRequests(3, 10000);
          }, 30000);
      }
      
      function sendRequests(attemptsLeft, interval) {
          if (attemptsLeft <= 0) {
              openModal('Provisioning Failed', 'Failed to provision device. Please try again.');
              resetProvisionForm();
              return;
          }
      
          // Send GET request to check AWS provisioning status
          fetch('/aws-provisioning-status')
          .then(response => {
              if (!response.ok) {
                  throw new Error('Failed to get AWS provisioning status.');
              }
              return response.text();
          })
          .then(status => {
              if (status === 'Unauthorized User Initializing Certificate') {
                  openModal('Unauthorized', 'Unauthorized User Initializing Certificate');
                  resetProvisionForm();
              } else if (status === 'Device Provisioned connected successfully!') {
                  openModal('Provisioned', 'Device Provisioned connected successfully!');
                  handleAWSConnection();
              } else {
                  // Provisioning in progress, wait and check again
                  setTimeout(() => {
                      sendRequests(attemptsLeft - 1, interval);
                  }, interval);
              }
          })
          .catch(error => {
              // Handle any errors during fetch or processing
              openModal('Error', error.message);
              resetProvisionForm();
          });
      }
      
      
      function resetProvisionForm() {
        $('loader').classList.add('hide');
        $('main-box').classList.remove('hide');
        $('wifi-box-initialized').classList.remove('hide');
        $('system').value = '';
        $('access-key').value = '';
        $('secret-access-key').value = '';
      }
      
      // Counter to keep track of the number of additional fields
      // Counter to keep track of the number of additional fields
      var fieldCounter = 0;
      
      // Function to add a new dropdown field
      function addField() {
          var additionalFields = document.getElementById('additional-fields');
          var fieldId = 'sensor-' + fieldCounter; // Unique ID for the field
          var wrapper = document.createElement('div');
          wrapper.className = 'tf-wrapper';
      
          var label = document.createElement('label');
          label.setAttribute('for', fieldId);
          label.className = 'input-label';
          label.textContent = 'Sensor ' + (fieldCounter + 1);
      
          var select = document.createElement('select');
          select.id = fieldId;
          var options = ["Thermocouples", 
          "Digital Temperature Sensors", "Infrared Temperature Sensors",
          
          "Capacitive Humidity Sensors", "Resistive Humidity Sensors", 
          "Thermal Conductivity Humidity Sensors", "Gravimetric Humidity Sensors",
          
          "Soil Moisture Sensors", "Capacitive Moisture Sensors", 
          "Resistive Moisture Sensors", "Optical Moisture Sensors",
          
          "Photodiodes", "Phototransistors", "Light-Dependent Resistors (LDRs)", 
          "Photovoltaic Cells", "Ambient Light Sensors",
          
          "Passive Infrared (PIR) Motion Sensors", "Ultrasonic Motion Sensors", 
          "Microwave Motion Sensors", "Accelerometers", "Gyroscopes",
          
          "Inductive Proximity Sensors", "Capacitive Proximity Sensors", 
          "Ultrasonic Proximity Sensors", "Infrared Proximity Sensors",
          
          "Piezoelectric Pressure Sensors", "Strain Gauge Pressure Sensors", 
          "Capacitive Pressure Sensors", "Resonant Pressure Sensors", "Optical Pressure Sensors",
          
          "Carbon Monoxide (CO) Sensors", "Carbon Dioxide (CO2) Sensors", 
          "Oxygen (O2) Sensors", "Methane (CH4) Sensors", "Volatile Organic Compound (VOC) Sensors",
          
          "Microphones", "Sound Level Sensors", "Acoustic Wave Sensors", 
          "Piezoelectric Sensors", "MEMS Microphones",
          
          "Fingerprint Sensors", "Retinal Scanners", "Iris Scanners", 
          "Heart Rate Sensors", "Blood Oxygen Sensors",
          
          "pH Sensors", "Gas Chromatography Sensors", 
          "Ion-Selective Electrodes", "Electrochemical Sensors", "Biosensors",
        
          "pH Sensors", "Dissolved Oxygen Sensors", 
          "Turbidity Sensors", "Conductivity Sensors", "Chlorine Sensors"] // Your pre-existing list of options
          for (var i = 0; i < options.length; i++) {
              var option = document.createElement('option');
              option.text = options[i];
              select.add(option);
          }
      
          wrapper.appendChild(label);
          wrapper.appendChild(select);
          additionalFields.appendChild(wrapper);
          fieldCounter++;
      }
      
      // Function to remove the last dropdown field
      function removeField() {
          var additionalFields = document.getElementById('additional-fields');
          var children = additionalFields.children;
          if (children.length > 0) {
              additionalFields.removeChild(children[children.length - 1]);
              fieldCounter--;
          }
      }
    
      // Function to periodically send requests for control and sensor info
    function sendDataRequests() {
        // Check if aws-box-initialized is not hidden
        var awsBox = document.getElementById('aws-box-initialized');
        if (awsBox && !awsBox.classList.contains('hidden')) {
            // Send requests for control and sensor info
            setInterval(function() {
                // Send request for control and sensor info
                fetchControlAndSensorInfo();
            }, 100000); // Send requests every 10 seconds
        }
    }
    
function fetchControlAndSensorInfo() {
    console.log('Sending GET request to server endpoint: /control-sensor-info');
    // Send GET request to server endpoint
    fetch('/control-sensor-info')
    .then(response => {
        console.log('Received response from server:', response);
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        console.log('Received data from server:', data);
        // Update UI with control and sensor messages
        updateControlAndSensorInfo(data.controlMessage, data.sensorMessage);
    })
    .catch(error => {
        console.error('There was a problem with the fetch operation:', error);
    });
}


// Function to update UI with control and sensor messages
function updateControlAndSensorInfo(controlMessage, sensorMessage) {
    // Get the elements where the messages will be displayed
    console.log(controlMessage);
    var controlMessageElement = document.getElementById('control-message');

    // Check if control message is provided and update the UI
    if (typeof controlMessage === 'object') {
        // If controlMessage is an object, convert it to a string
        controlMessage = JSON.stringify(controlMessage);
    }
    

    // Update the UI with the messages
    controlMessageElement.textContent = controlMessage;
}

// Call the function to send requests for control and sensor info
sendDataRequests();
      
      // Event listener for add field button
      document.getElementById('add-field-btn').addEventListener('click', addField);
      
      // Event listener for remove field button
      document.getElementById('remove-field-btn').addEventListener('click', removeField);
      
      // Initializes the app.
      $('svg-eye').innerHTML = svgEye;
      $('svg-no-eye').innerHTML = svgNoEye;
      $('img-logo').innerHTML = svgLogo;
      $('svg-connect').innerHTML = svgConnect;
      
      
      $('show-hide-password').addEventListener('click', showHidePassword);
      $('connect-wifi').addEventListener('click', doConnection);
      $('connect-aws').addEventListener('click', doProvision);
      $('enterprise-wifi-toggle').addEventListener('change', function() {
        if (this.checked) {
          show('conf-wifi');
        }
        else {
          hide('conf-wifi');
        }
      });
          </script>
</body>
</html>
)=====";

#endif






