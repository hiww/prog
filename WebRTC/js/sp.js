var recognition3 = new webkitSpeechRecognition();
recognition3.lang = "ja-JP";
recognition3.interimResults = true;
recognition3.continuous = true;
recognition3.onsoundstart = function() {
    $("#state3").text("認識中");
};
recognition3.onnomatch = function() {
    $("#recognizedText3").text("もう一度試してください");
};
recognition3.onerror= function() {
    $("#recognizedText3").text("エラー");
};
recognition3.onsoundend = function() {
    $("#state3").text("停止中");
};
recognition3.onresult = function(event) {
    var results = event.results;
    for (var i = event.resultIndex; i < results.length; i++) {
        if (results[i].isFinal) {
            $("#recognizedText3").text(results[i][0].transcript);
        } else {
            $("#recognizedText3").text(results[i][0].transcript);
        }
    }
};