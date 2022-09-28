#include <CCsv.h>

CCsv::
CCsv(const std::string &filename) :
 filename_(filename)
{
}

bool
CCsv::
load()
{
  if (loaded_)
    return loadRc_;

  loaded_ = true;
  loadRc_ = false;

  //---

  bool commentHeader   = isCommentHeader  ();
  bool firstLineHeader = isFirstLineHeader();
  bool allowComments   = isAllowComments  ();

  data_.clear();

  if (! open())
    return loadRc_;

  std::string line;

  while (readLine(line)) {
    if (line.empty())
      continue;

    std::string comment;
    CommentType commentType { CommentType::NONE };

    if (isComment(line, comment, commentType)) {
      if      (commentType == CommentType::META_START) {
        inMeta_ = true;
        continue;
      }
      else if (commentType == CommentType::META_END) {
        inMeta_ = false;
        continue;
      }
      else if (inMeta_) {
        Fields strs;

        if (! stringToFields(comment, strs))
          continue;

        // TODO: skip first line

        meta_.push_back(std::move(strs));

        continue;
      }
      else {
        if (commentHeader) {
          Fields strs;

          if (! stringToFields(comment, strs))
            continue;

          header_ = std::move(strs);

          commentHeader   = false;
          firstLineHeader = false;

          continue;
        }
        else {
          if (allowComments)
            continue;
        }
      }
    }

    //---

    Fields strs;

    if (! stringToFields(line, strs))
      continue;

    //---

    if (firstLineHeader) {
      header_ = std::move(strs);

      commentHeader   = false;
      firstLineHeader = false;

      continue;
    }

    //---

    data_.push_back(std::move(strs));
  }

  close();

  loadRc_ = true;

  return loadRc_;
}

bool
CCsv::
getFields(const Inds &inds, Data &data) const
{
  auto *th = const_cast<CCsv *>(this);

  if (! th->load())
    return false;

  for (const auto &fields : data_) {
    Fields fields1;

    if (! inds.empty()) {
      for (uint i = 0; i < inds.size(); ++i) {
        int ind = inds[i];

        if (ind >= 1 && ind <= int(fields.size()))
          fields1.push_back(fields[uint(ind - 1)]);
        else
          fields1.push_back("");
      }
    }
    else {
      fields1 = fields;
    }

    data.push_back(std::move(fields1));
  }

  return true;
}

bool
CCsv::
getFields(Data &data) const
{
  auto *th = const_cast<CCsv *>(this);

  if (! th->load())
    return false;

  data = data_;

  return true;
}

bool
CCsv::
stringToColumns(const std::string &str, Fields &strs)
{
  return stringToSubFields(str, strs);
}

bool
CCsv::
open() const
{
  fp_ = fopen(filename_.c_str(), "r");
  if (! fp_) return false;

  return true;
}

void
CCsv::
close() const
{
  if (fp_)
    fclose(fp_);

  fp_ = nullptr;
}

bool
CCsv::
isComment(const std::string &line, std::string &comment, CommentType &type) const
{
  uint i = 0;

  skipSpace(line, i);

  if (line[i] != '#')
    return false;

  ++i;

  skipSpace(line, i);

  comment = line.substr(i);

  if      (comment == "META_DATA")
    type = CommentType::META_START;
  else if (comment == "END_META_DATA")
    type = CommentType::META_END;

  return true;
}

bool
CCsv::
readLine(std::string &line) const
{
  line = "";

  if (feof(fp_)) return false;

  int c = fgetc(fp_);

  if (c == EOF)
    return false;

  while (! feof(fp_) && c != '\n') {
    line += char(c);

    c = fgetc(fp_);
  }

  return true;
}

bool
CCsv::
stringToFields(std::string &line, Fields &strs) const
{
  std::vector<Fields> strsArray;

  Fields strs1;

  if (! stringToSubFields(line, strs1))
    return false;

  strsArray.push_back(std::move(strs1));

  //---

  auto na = strsArray.size();

  if (na == 0)
    return false;

  //---

  for (uint i = 0; i < na; ++i) {
    const Fields &strs2 = strsArray[i];

    if (i > 0) {
      std::string ls = strs.back() + '\n';

      strs.pop_back();

      auto ns1 = strs2.size();

      if (ns1 > 0)
        strs.push_back(ls + strs2[0]);
      else
        strs.push_back(std::move(ls));

      for (uint j = 1; j < ns1; ++j)
        strs.push_back(strs2[j]);
    }
    else {
      for (const auto &s : strs2)
        strs.push_back(s);
    }
  }

  return true;
}

bool
CCsv::
stringToSubFields(const std::string &str, Fields &strs) const
{
  static char dquote = '\"';

  str_ = str;
  len_ = uint(str_.size());
  pos_ = 0;

  while (pos_ < len_) {
    std::string str1;

    while (pos_ < len_ && str_[pos_] != separator_) {
      if (str_[pos_] == dquote) {
        // skip double quote
        ++pos_;

        // skip string
        std::string pstr;

        parseString(pstr);

        str1 += std::move(pstr);
      }
      else {
        // skip to field separator
        uint j = pos_;

        while (pos_ < len_ && str_[pos_] != separator_)
          ++pos_;

        str1 += str_.substr(j, pos_ - j);

        break;
      }
    }

    // skip field separator
    if (pos_ < len_ && str_[pos_] == separator_)
      ++pos_;

    // add to return list
    strs.push_back(std::move(str1));
  }

  return true;
}

void
CCsv::
parseString(std::string &str) const
{
  static char dquote = '\"';

  bool terminated = false;

  while (! terminated) {
    while (pos_ < len_) {
      if (str_[pos_] == dquote) {
        ++pos_;

        if (pos_ < len_ && str_[pos_] == dquote) {
          str += dquote;

          ++pos_;
        }
        else {
          terminated = true;
          break;
        }
      }
      else
        str += str_[pos_++];
    }

    if (! terminated) {
      if (readLine(str_)) {
        len_ = uint(str_.size());
        pos_ = 0;
      }
      else
        terminated = true;
    }
  }
}

void
CCsv::
skipSpace(const std::string &str, uint &i) const
{
  auto len = str.size();

  while (i < len && isspace(str[i]))
    ++i;
}
