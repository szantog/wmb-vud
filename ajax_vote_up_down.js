// $Id$

Drupal.voteUpDownAutoAttach = function() {
  var vdb = [];
  $('span.vote-up-inact, span.vote-down-inact, span.vote-up-act, span.vote-down-act').each(function () {
    // Read in the path to the PHP handler
    var uri = $(this).attr('title');
    // Get title from a tag.
    var atitle = $(this).children('a').attr('title');
    $(this).attr('title', atitle);
    // remove href link
    $(this).html('');
    // Create an object with this uri. Because
    // we feed in the span as an argument, we'll be able
    // to attach events to this element.
    if (!vdb[uri]) {
      vdb[uri] = new Drupal.VDB(this, uri);
    }
  });
}

/**
 * A Vote DataBase object
 */
Drupal.VDB = function(elt, uri) {
  var db = this;
  // By making the span element a property of this object,
  // we get the ability to attach behaviours to that element.
  this.elt = elt;
  this.uri = uri;
  this.id = $(elt).attr('id');
  this.type = this.id.indexOf('node') > -1 ? 'node' : 'comment';
  this.dir1 = this.id.indexOf('vote_up') > -1 ? 'up' : 'down';
  this.dir2 = this.dir1 == 'up' ? 'down' : 'up';
  // Extract the cid so we can change other elements for the same cid
  this.cid = db.id.match(/[0-9]+$/);
  $(elt).click(function() {
    // Ajax GET request for vote data
    $.ajax({
      type: "GET",
      url: db.uri,
      success: function (data) {
        //update the voting arrows
        $('#' + db.id + '.vote-' + db.dir1 + '-inact')
          .removeClass('vote-' + db.dir1 + '-inact')
          .addClass('vote-' + db.dir1 + '-act');
        $('#vote_' + db.dir2 + '_' + db.type + '_' + db.cid)
          .removeClass('vote-' + db.dir2 + '-act')
          .addClass('vote-' + db.dir2 + '-inact');
        // update the points
        $('#vote_points_' + db.type + '_' + db.cid).html(data);
      },
      error: function (xmlhttp) {
        alert('An HTTP error '+ xmlhttp.status +' occured.\n'+ db.uri);
      }
    });
  });
}

// Global killswitch
if (Drupal.jsEnabled) {
  $(document).ready(Drupal.voteUpDownAutoAttach);
}
