str defaultPath = "~/wallpapers"

ArrayList<Wallpapaper> wallpapapers = ArrayList<Wallpapaper>();

@StartProgram
fun main(str[] args) {
  if (agrs.length == 0) {
    help();
    return Fanat.exit(0);
  }
  str cmd = args[0];
  str[] newArgs;
  if (args.length > 1) newArgs = &args[1];
  else newArgs = [];
}

fun runCommand(str command, str[] args) <- ResultCode {
  return @ConstStringWhen when (command) {
    "reloadWallpapers" -> reloadWallpapers(args);
    "reloadSocket" -> reloadSocket(args);
    "reload" -> reload(args);
    "exit" -> exit(args);
    "select" -> select(args);
  }
}
enum ResultCode {
  SUCCESS,
  ERROR,
}

fun reloadWallpapers(str[] args) {
  wallpapapers = ArrayList<Wallpapaper>();
  
  enum Sorting {

  }

  str path;
  for (u16 i = 0; i < args.length; i++) {
    str arg = args[i];
    when (arg) {
      "folder" -> path = (++i < args.length) ? args[++i] : return Fanat.error(1);
      "sorting" -> sorting = Sorting.by(args[++i]) | defaultPath;
      ""
    }
  }
}
