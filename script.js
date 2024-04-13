/*link tree*/
var toggler = document.getElementsByClassName("caret");
var i;

for (i = 0; i < toggler.length; i++) {
  toggler[i].addEventListener("click", function () {
    this.parentElement.querySelector(".nested").classList.toggle("active");
    this.classList.toggle("caret-down");
  });
}

//lazy loading images 
$(document).ready(function() {
  var lazyloadImages;    

  if ("IntersectionObserver" in window) {
    lazyloadImages = document.querySelectorAll(".lazy");
    var imageObserver = new IntersectionObserver(function(entries, observer) {
      entries.forEach(function(entry) {
        if (entry.isIntersecting) {
          var image = entry.target;
          image.src = image.dataset.src;
          image.classList.remove("lazy");
          imageObserver.unobserve(image);
        }
      });
    });

    lazyloadImages.forEach(function(image) {
      imageObserver.observe(image);
    });
  } else {  
    var lazyloadThrottleTimeout;
    lazyloadImages = $(".lazy");
    
    function lazyload () {
      if(lazyloadThrottleTimeout) {
        clearTimeout(lazyloadThrottleTimeout);
      }    

      lazyloadThrottleTimeout = setTimeout(function() {
          var scrollTop = $(window).scrollTop();
          lazyloadImages.each(function() {
              var el = $(this);
              if(el.offset().top - scrollTop < window.innerHeight) {
                var url = el.attr("data-src");
                el.attr("src", url);
                el.removeClass("lazy");
                lazyloadImages = $(".lazy");
              }
          });
          if(lazyloadImages.length == 0) { 
            $(document).off("scroll");
            $(window).off("resize");
          }
      }, 20);
    }

    $(document).on("scroll", lazyload);
    $(window).on("resize", lazyload);
  }
})