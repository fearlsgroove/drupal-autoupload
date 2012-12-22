AutoUpload is a user interface (UI) enhancement for uploading files.

Currently, users must select files, then press the "Upload" button. We
found users often don't realize a button press is necessary and mistakenly
think their image is uploaded when it's not.

This module removes the extra button press and hides the "Upload" button
via JavaScript for a quicker file upload UI. When JavaScript is not
enabled, it falls back to the "Upload" button.

Developed by RMR Labz (http://www.rmrlabz.com).

==================

Handles the core managed file fields and Media module file fields.

Configure the type of file fields you want to use auto upload at
admin/config/media/autoupload.
