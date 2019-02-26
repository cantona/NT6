// board.h

// 表名前綴
#define TABLE_PREFIX    "phpbb_"

#define TOPICS_TABLE    TABLE_PREFIX "topics"
#define FORUMS_TABLE    TABLE_PREFIX "forums"

#define POSTS_TABLE     TABLE_PREFIX "posts"
#define TEXTS_TABLE     TABLE_PREFIX "posts_text"

#define USERS_TABLE     TABLE_PREFIX "users"

#define DEBUG_MSG(x)    tell_object(find_player("lonely"), HIR + x + NOR);

#define POST_ID         0       // 文章編號
#define TOPIC_ID        1       // 主題編號
#define POSTER_ID       2       // 文章作者
#define POST_TIME       3       // 發表時間

#define POST_SUBJECT    0       // 文章標題
#define BBCODE_UID      1       // bbcode 的鑑定號
#define POST_TEXT       2       // 文章內容

#define TOPIC_TITLE     0       // 主題標題
#define TOPIC_POSTER    2       // 主題作者
#define TOPIC_TIME      3       // 發表時間
#define TOPIC_VIEWS     4       // 主題瀏覽次數
#define TOPIC_REPLIES   5       // 主題回覆
#define TOPIC_FIRST_ID  6       // 主題首貼編號

// BBS 模式(顯示所有的文章，包括回覆)
int is_bbs_mode(object me) { return (me->query("env/board_mode") == 0); }
// Web 論壇模式(只顯示主題，回覆在察看主題時再顯示)
// int is_web_mode(object me) { return (me->query("env/board_mode") == 1); }
int is_web_mode(object me) { return me->query("env/board_mode"); }

// 顯示回覆的方式
#define SHOW_NONE       0       // 不顯示
#define SHOW_LAST       1       // 顯示最後一篇
#define SHOW_ALL        2       // 顯示所有

// Web 論壇地址
#define WEB_URL         "http://www.mudbuilder.com/phpbb/"
#define FORUM_URL       WEB_URL "viewforum.php?f=%d"    // 版面頁面地址
#define TOPIC_URL       WEB_URL "viewtopic.php?t=%d"    // 主題頁面地址

