<?php if(!empty($_POST['submit'])){  echo 'date is ' ;  echo $_POST['edate'];  }?><form action="test.php" name="test" id="test" method="post">  Date : <input type="date" name="edate">  <input type="submit" name="submit" value="submit">  </form>