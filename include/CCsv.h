#ifndef CCsv_H
#define CCsv_H

#include <cstdio>
#include <string>
#include <vector>
#include <cassert>

/*!
 * \brief Load CSV file
 */
class CCsv {
 public:
  using Inds   = std::vector<int>;
  using Fields = std::vector<std::string>;
  using Data   = std::vector<Fields>;

  enum CommentType {
    NONE,
    META_START,
    META_END
  };

 public:
  explicit CCsv(const std::string &filename="");

  //! get/set filename
  const std::string &filename() const { return filename_; }
  void setFilename(const std::string &filename) { filename_ = filename; }

  //! get header fields
  const Fields &header() const { assert(loaded_); return header_; }

  //! get row data
  const Data &data() const { assert(loaded_); return data_; }

  //! get meta data
  bool hasMeta() const { return ! meta_.empty(); }
  const Data &meta() const { assert(loaded_); return meta_; }

  //---

  //! get/set has comment header
  bool isCommentHeader() const { return commentHeader_; }
  void setCommentHeader(bool b) { commentHeader_ = b; }

  //! get/set first line is header
  bool isFirstLineHeader() const { return firstLineHeader_; }
  void setFirstLineHeader(bool b) { firstLineHeader_ = b; }

  //! get/set allow comment lines
  bool isAllowComments() const { return allowComments_; }
  void setAllowComments(bool b) { allowComments_ = b; }

  //! get/set separator (default comma)
  const char &separator() const { return separator_; }
  void setSeparator(const char &c) { separator_ = c; }

  //---

  bool load();

  bool getFields(const Inds &inds, Data &data) const;

  bool getFields(Data &data) const;

  bool stringToColumns(const std::string &str, Fields &strs);

 private:
  bool open () const;
  void close() const;

  // get is command and check for meta start/end
  bool isComment(const std::string &line, std::string &comment, CommentType &type) const;

  // read line from file
  bool readLine(std::string &line) const;

  // convert string to separated fields
  bool stringToFields(std::string &line, Fields &strs) const;

  // convert string to separated fields
  bool stringToSubFields(const std::string &str, Fields &strs) const;

  // parse string (will read extra lines)
  void parseString(std::string &str) const;

  // skip spaces
  void skipSpace(const std::string &str, int &i) const;

 private:
  std::string         filename_;                  //! csv filename
  bool                loaded_          { false }; //! is file loaded
  bool                loadRc_          { false }; //! load return code
  Fields              header_;                    //! header fields
  Data                data_;                      //! data rows
  Data                meta_;                      //! meta data
  bool                commentHeader_   { true };  //! is comment header
  bool                firstLineHeader_ { false }; //! is first line header
  bool                allowComments_   { true };  //! allow comments
  char                separator_       { ',' };   //! separator
  bool                inMeta_          { false }; //! parse in meta data
  mutable FILE*       fp_              { 0 };     //! open file pointer
  mutable std::string str_;                       //! temp work string
  mutable int         len_             { 0 };     //! temp work string length
  mutable int         pos_             { 0 };     //! temp work string position
};

#endif
