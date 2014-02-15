
onmessage = function(oEvent){
	if (oEvent.data == "play")
		startPlay();
	else if ( oEvent.data == "pause"){
		stopPlay();
	}
}




function startPlay(){
	var viewPlayer = setInterval('play()',1000);
}

function play(){
	postMessage("nextPlay");
}

function stopPlay(){
	clearInterval(this.viewPlayer);
}