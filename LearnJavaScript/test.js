// ==UserScript==
// @name         视频加速与时间加速demo
// @namespace    https://bbs.tampermonkey.net.cn/
// @version      0.1
// @description  用于:http://time.tianqi.com/的时间加速和用于bilibili的一个视频倍速:https://www.bilibili.com/video/BV1ys411p7To
// @author       王一之
// @match        http://time.tianqi.com/
// @match        https://www.bilibili.com/video/*
// @run-at       document-start
// @grant        none
// ==/UserScript==

let rate = 4; // 倍速

if (location.href.indexOf('time.tianqi.com') !== -1) {
    let hookSetInterval = setInterval;
    setInterval = function(a, b) {
        return hookSetInterval(a, b / rate);
    };
} else {
    window.onload = function() {
        const video = document.querySelector('video');
        if (video) {
            video.onplay = function() {
                video.playbackRate = rate;
            };
        }
    };
}
