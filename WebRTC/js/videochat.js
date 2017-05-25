// Get the method for access the camera and microphone.
navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
var localStream;    // Store the my stream.
var connectedCall;  // Save the call value with connected.

// Connect to the SkyWay-API.(https://skyway.io)
var peer = new Peer({ key: '/* Replace your API-Key.*/', debug: 3});

// When established connection, call the open event.
peer.on('open', function() {
    $('#my-id').text(peer.id);
});

// We can send video each other.
peer.on('call', function(call) {
  　
    // Save call-object.
    connectedCall = call;
    $("#peer-id").text(call.peer);

    //  Select the stream-object from getUserMedia.
    call.answer(localStream);

    // When recieved the other stream, call the stream event.
    call.on('stream', function(stream) {

        // Convert the stream-object to URL. (for show in the html5)
        var url = URL.createObjectURL(stream);

        // Preview the video in src.
        $('#peer-video').prop('src', url);
    });
});

// DOM-contents event.
$(function() {

    // Get the stream of camera and microphone.
    navigator.getUserMedia({audio: true, video: true}, function(stream) {

        // Save  the stream.
        localStream = stream;
        var url = URL.createObjectURL(stream);
        $('#my-video').prop('src', url);
    }, function() { alert("Error!"); });

    // Start of behavior.
    $('#call-start').click(function() {

        // Read the ID from form.
        var peer_id = $('#peer-id-input').val();
        var call = peer.call(peer_id, localStream);
        call.on('stream', function(stream) {

            // Show other ID.
            $("#peer-id").text(call.peer);
            var url = URL.createObjectURL(stream);
            $('#peer-video').prop('src', url);
        });
    });

    // End of behavior.
    $('#call-end').click(function() {

        // Close the video.
        connectedCall.close();
    });
});