/*trails JavaScript*/
function movepic(){
  document.getElementById("changemypic").src = "./image/colorado-golden-gate-canyon-state-park_cd38fae7a4757643c8cbb7849ad01941.jpg"
}

function resetpic(){
  document.getElementById("changemypic").src = "Golden_Gate_YNP1.jpg"
}

function movepic1(){
  document.getElementById("changemypic1").src = "./image/1.jpg"
}
function resetpic1(){
  document.getElementById("changemypic1").src = "park.jpg"
}
function movepic2(){
  document.getElementById("changemypic2").src = "./image/2.jpg"
}
function resetpic2(){
  document.getElementById("changemypic2").src = "Eldora-Colorado-Forestry.jpg"
}
function movepic3(){
  document.getElementById("changemypic3").src = "./image/3.jpg"
}
function resetpic3(){
  document.getElementById("changemypic3").src = "img_0339.jpg"
}



/* all JavaScript*/
var i = 0;

function changepic(){
  i+=1;
  document.getElementById("changepic").src = "./image/"+i+".jpg";

  if(i>6){
    i=0;
  }
}

function changepic2(){
  i-=1;
  document.getElementById("changepic").src = "./image/"+i+".jpg";
  if(i<0){
    i=6;
  }
}

function dark(){
  document.getElementById("allbody").className = "dark";
}
function light(){
  document.getElementById("allbody").className = "";
}

function more(){

  var text = "Golden Gate Canyon State Park encompasses over 12,000 acres of forest, with rocky peaks, aspen meadows."+
  "This 11,998-acre Front Range park established in 1960 has campgrounds, picnic areas, and 36 miles of hiking trails for hiking,"+
  "horseback riding, mountain biking and offer the snow lover ample opportunities for outdoor recreation such as cross-country skiing,"+
  " snowshoeing, sledding, ice fishing and ice skating.Only 30 miles from Denver, this Colorado State Park makes for a great weekend trip,"+
  " location for your next family or company outing, or makes a great stop on a road trip. The park offers varied camping amenities such "+
  "as a electrical hook-ups and tent-sites in two different campgrounds or one of the five cabins and two yurts. "+
  "Here, you will also find stocked fishing ponds, picnic sites and the Panorama Point Scenic Overlook, where you will "+
  "look out over the Continental Divide. The park is also home to mule deer, mountain lions, black bear, and other wildlife."+
  "Check with the visitor center for information on hunting or renting out the guest house. "+
  "You can also camp in one of the first come first served backcountry campsites, but be aware that no campfires are allowed."
  document.getElementById("desc").innerHTML = text;
}
