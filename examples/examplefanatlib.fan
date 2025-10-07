@MutableFields(mutateFor=VALUE, logic = (value, structure, analyzer) -> {
  bool isUsed = false;
  analyzer.searchValueUsage(value).foreach (usage, break_) => {
    if (usage instanceof AccessFieldValueUsage usage) {
      if (usage.getField() == Str::len) {
        flag = true;
        break_();
      }
    }
  }.ifNotAllFound () -> isUsed = true;

  if (!isUsed) {
    MutableFields.remove(Str::len);
    /*
      fun remove(variable) {
        variable.addMark(MutableField.REMOVE_MARK);
      }
    */
  }
})
struct Str {
  private char[] chs;
  public
  @RemovableField(removable=true)
  @MutableU(mode=MINIMUM)
  Un len;

  public Str(char[] chs) {
    precompile (analyzer) {
      if (analyzer.thereArraySize(chs) && analyzer.thereField(*this.len)) {
        inruntime {
          
        }
      }
    }
  }
}
