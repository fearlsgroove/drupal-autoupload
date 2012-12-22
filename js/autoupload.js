/*
 * Behavior for the automatic file upload
 */

(function ($) {
  Drupal.behaviors.autoUpload = {
    attach: function (context, settings) {
      /*
       * selectors is an associative array. for more info, see
       * _autoupload_get_predefined in autoupload.admin.inc
       */
      var selectors = settings.autoupload.selectors;

      $.each(selectors, function (index, value) {
        var fs_context = value['context'];
        $(fs_context, context).each(function () {
          var $wrapper = $(this);
          var file_input = value['file_input'];
          var file_event = value['file_event'];
          var submit_input = value['submit_input'];
          var submit_event = value['submit_event'];
          var error = value['error'];
          var error_remove = value['error_remove'];

          /*
           * add CSS to the document instead of .hide(), because the element
           * may be added dynamically after this point. cannot delegate "load"
           */
          $('head').append($('<' + 'style media="all" type="text/css"' + '>' + fs_context + ' ' + submit_input + ' { display:none; }<' + '/style' + '>'));

          $wrapper.delegate(file_input, file_event, function (e) {
            if (!error || $(this).hasClass('autoupload-processed')) {
              //no error check or error check has been performed

              setTimeout(function () {
                //allow for validation. (prefer event, but there isn't one)
                if (!$wrapper.find(error).length > 0) {
                  $wrapper.find(submit_input).trigger(submit_event);
                }
              }, 100);
            }
            else if (error) {
              //perform error check
              e.preventDefault();

              if (!error_remove) {
                //error removal is handled already. no need to do anything
              }
              if (error_remove == 'id') {
                var elem_id = error.substr(error.lastIndexOf('#') + 1);
                if (!/[: .[]+/.test(elem_class)) {
                  $wrapper.find(error).removeAttr(elem_id);
                }
              }
              else if (error_remove == 'class') {
                var elem_class = error.substr(error.lastIndexOf('.') + 1);
                if (!/[: #[]+/.test(elem_class)) {
                  $wrapper.find(error).removeClass(elem_class);
                }
              }
              else if (error_remove == 'element') {
                $wrapper.find(error).remove();
              }

              $(this).addClass('autoupload-processed');
              $(this).trigger(file_event);
            }
          });
        });
      });

      /*
       * Media module's cancel button is added after load, so delay for a
       * moment then resize the media browser so the cancel button is visible
       */
      if (settings.autoupload.predefined.media && Drupal && Drupal.media && Drupal.media.browser && typeof Drupal.media.browser.resizeIframe == 'function') {
        setTimeout(function () {
          Drupal.media.browser.resizeIframe();
        }, 100);
      }
    }
  };
})(jQuery);
