# token_parser
Token parser. Parse string to tokens.


## USAGE:

### 1.
TokenParser::Settings::TokenIds token_ids;\
token_ids.insert({0, ";"});\
token_ids.insert({1, "("});\
token_ids.insert({2, ")"});\
token_ids.insert({3, "{"});\
token_ids.insert({4, "}"});\
token_ids.insert({5, "int"});\
token_ids.insert({6, "int32_t"});\
token_ids.insert({7, "="});\
TokenParser::Settings settings;\
settings.SetTokenIds(token_ids);\
settings.SetWordDelim(settings.GetWordDelimChars() + ";(){}=");\
settings.SetTokenIdIsFullWord(true);\
TokenParser::Parser parser(settings);

std::string str = "int32_t main() { int a=3.3; }";\
parser.SetStr(&str);

TokenParser::Token token_int32_t = parser.NextId();   // GetId() == 6\
std::string word_main = parser.NextWord();            // word == "main"\
TokenParser::Token token_ob = parser.NextId();        // GetId() == 1\
TokenParser::Token token_cb = parser.NextId();        // GetId() == 2\
TokenParser::Token token_ob2 = parser.NextId();       // GetId() == 3\
TokenParser::Token token_int = parser.NextId();       // GetId() == 5\
std::string word_a = parser.NextWord();               // word == "a"\
TokenParser::Token token_eq = parser.NextId();        // GetId() == 7\
TokenParser::Token token_float = parser.NextFloat();  // GetFloat() == 3.3\
TokenParser::Token token_semicolon = parser.NextId(); // GetId() == 0\
TokenParser::Token token_cb2 = parser.NextId();       // GetId() == 4\
TokenParser::Token token_null = parser.NextId();      // IsNull() == true

### 2.
TokenParser::Settings::TokenIds token_ids;\
token_ids.insert({0, "sin"});\
token_ids.insert({1, "cos"});\
TokenParser::Settings settings;\
settings.SetTokenIds(token_ids);\
settings.SetTokenIdIsFullWord(false);\
TokenParser::Parser parser(settings);

std::string str = "sincos";\
parser.SetStr(&str);

TokenParser::Token token_sin = parser.NextId();   // GetId() == 0\
TokenParser::Token token_cos = parser.NextId();   // GetId() == 1
