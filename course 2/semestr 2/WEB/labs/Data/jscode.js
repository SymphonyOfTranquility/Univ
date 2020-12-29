var feedback = document.getElementById('feedback');

function fadeIn()
{
  var op = 0.1;
  feedback.style.display = 'block';
  var timer = setInterval(function ()
  {
    if (op >= 1)
      clearInterval(timer);
    feedback.style.opacity = op;
    feedback.style.filter = 'alpha(opacity = ' + op*100 + ')';
    op += 0.05;
  } , 20);
}

function fadeOut()
{
  var op = 1;
  feedback.style.display = 'block';
  var timer = setInterval(function ()
  {
    if (op <= 0.05)
    {
      clearInterval(timer);
      feedback.style.display = 'none';
    }
    feedback.style.opacity = op;
    feedback.style.filter = 'alpha(opacity = ' + op*100 + ')';
    op -= 0.05;
  } , 20);
}

var inputUsName = document.getElementById('username');
inputUsName.oninvalid = function(event) 
{
    event.target.setCustomValidity('Username should only contain latin letters(Maximum 15 letters). e.g. John');
}

var inputPhone = document.getElementById('phone');
inputPhone.oninvalid = function(event) 
{
    event.target.setCustomValidity('Input phone number as on example: +123(45)678-90-12');
}

