// dboard.c

#include <ansi.h>
#include <board.h>

#define BOARD_CAPACITY query("capacity")

inherit ITEM;

// 是否討論板？
int is_board()  { return 1; }

// create() 時調用，主要用於根據數據庫內保留的信息設置
// 版面的長描述。
void setup()
{
        string loc;
        string my_long, my_id;

        if (stringp(loc = query("location")))
                move(loc);
        /*
        my_long = BOARD_D->query_forum_info(this_object(),
                                            "forum_desc");
        */
        my_long = query("long");
        my_id = query("board_id");

        set("no_get", 1);
        set("long", my_long + "\n");
        set("id", my_id);
        set("location", loc);
}

void init()
{
        add_action("do_post", "post");
        add_action("do_read", "read");
        add_action("do_discard", "delete");
        add_action("do_discard", "discard");
}

// 版面的短描述，要返回未讀的文章/主題數。
string short()
{
        mapping *notes;
        int i, unread, last_read_time;
        object me;
        int mode;
        int time;
        int max;
        object ob;
        string str;

        if (! objectp(me = this_player()))
                return ::short();

        ob = this_object();
        mode = is_bbs_mode(me);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        notes = (mode ? BOARD_D->query_all_posts(ob)
                      : BOARD_D->query_all_topics(ob));
        time = (mode ? POST_TIME : TOPIC_TIME);

        str = mode ? "文章" : "主題";

        if (! arrayp(notes) || ! sizeof(notes))
                return ::short() + " [ 沒有任何" + str + " ]";

        last_read_time = query("board_last_read/" + query("board_id"), me);
        max = sizeof(notes) - 1;

        for (unread = 0, i = max; i >= 0; i--, unread++)
                if (notes[i][time] <= last_read_time) break;

        max++;
        if (unread)
                return sprintf(HIC + "%s" + NOR + " [ %d 篇%s，" + HIY + "%d" + NOR + " 篇" +
                               HIR + "未讀" + NOR + "]", ::short(), max, str, unread);
        else
                return sprintf("%s [ " WHT "%d" NOR " 篇%s ]", ::short(), max, str);
}

// 版面的長描述，返回所有文章/主題的列表。
string long()
{
        mixed *notes;
        mixed *pinfo, *tinfo;
        int i, last_time_read;
        string msg, title;
        object me;

        me = this_player();
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        // bbs 模式
        if (is_bbs_mode(me))
        {
                notes = BOARD_D->query_all_posts(this_object());
                msg = sprintf("『 " HIW "%s" NOR " 』(" WHT "%s" NOR ")\n%s"
                              "\n" WHT "目前所有的文章有：\n" NOR
                              "────────────────────────"
                              "─────────────\n", query("name"),
                              sprintf(FORUM_URL, query("forum_id")),
                              query("long"));
                if (! arrayp(notes) || ! sizeof(notes)) return query("long");

                last_time_read = query("board_last_read/" + query("board_id"), me);
                i = sizeof(notes) - 200;
                if (i < 0) i = 0;
                for (; i < sizeof(notes); i++)
                {
                        // 加上 1 參數則不返回 msg
                        pinfo = BOARD_D->query_post_info(notes[i][POST_ID], 1);
                        if (pinfo[POST_SUBJECT] == "")
                        {
                                tinfo = BOARD_D->query_topic_info(notes[i][TOPIC_ID]);
                                title = (sizeof(tinfo) ? ("Re: " + tinfo[TOPIC_TITLE])
                                                       : pinfo[POST_SUBJECT]);
                        }
                        else title = pinfo[POST_SUBJECT];

                        msg += sprintf(WHT "%s[%2d]" NOR "  %-40s " WHT "%s " NOR "(%s)\n",
                                       (notes[i][POST_TIME] > last_time_read ? HIY : WHT),
                                       i + 1, title,
                                       BOARD_D->query_user_name(notes[i][POSTER_ID]),
                                       ctime(notes[i][POST_TIME])[0..15]);
                }
                msg += "────────────────────────────"
                       "───[ " WHT "BBS 模式" NOR " ]\n\n";
        } else
        {
                // 加上 1 參數則不返回後三項
                notes = BOARD_D->query_all_topics(this_object(), 1);
                msg = sprintf("『 " HIW "%s" NOR " 』(" WHT "%s" NOR ")\n%s"
                              "\n" WHT "目前所有的主題有：\n" NOR
                              "────────────────────────"
                              "─────────────\n", query("name"),
                              sprintf(FORUM_URL, query("forum_id")),
                              query("long"));

                if (! arrayp(notes) || ! sizeof(notes)) return query("long");

                last_time_read = query("board_last_read/" + query("board_id"), me);
                i = sizeof(notes) - 200;
                if (i < 0) i = 0;
                for (; i < sizeof(notes); i++)
                {
                        msg += sprintf(WHT "%s[%2d]" NOR "  %-40s " WHT "%s " NOR "(%s)\n",
                                       (notes[i][TOPIC_TIME] > last_time_read ? HIY : WHT),
                                       i + 1, notes[i][TOPIC_TITLE],
                                       BOARD_D->query_user_name(notes[i][TOPIC_POSTER]),
                                       ctime(notes[i][TOPIC_TIME])[0..15]);
                }
                msg += "────────────────────────────"
                       "───[ " WHT "Web 模式" NOR " ]\n\n";
        }
        return msg;
}

// 這將被玩家物件中的 F_EDIT 呼叫
void done_post(object me, string title, string text)
{
        int i;
        mapping *notes;
        array lines;
        int topic_id;
        int mode;
        int num;
        object ob;

        if (! stringp(text))
                return;

        if (strlen(text) > 64 * 1024)
        {
                tell_object(me, "你的文章太長了，請略去一些不必要的。\n");
                return;
        }

        lines = explode(text, "\n");
        i = sizeof(lines);
        if (i > 2000)
        {
                tell_object(me, "你的文章太長了，請略去一些不必要的。\n");
                return;
        }

        if (i > 20 && strlen(text) / i < 10)
        {
                tell_object(me, "你的文章中短句太多了，請調整一下以便他人閲讀。\n");
                return;
        }

        while (i--)
        {
                // scan all lines
                if (strlen(lines[i]) > 300)
                {
                        tell_object(me, "你文章中有些行太長了，請分行以便他人閲讀。\n");
                        return;
                }
        }

        // 與瀏覽器方式兼容
        text = replace_string(text, "  ", "　");
        ob = this_object();
        mode = is_bbs_mode(me);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        if (title == "re last") topic_id = BOARD_D->query_number_topic(ob, -1, mode);
        if (sscanf(title, "re last %d", num)) topic_id = BOARD_D->query_number_topic(ob, -num, mode);
        if (sscanf(title, "re %d", num)) topic_id = BOARD_D->query_number_topic(ob, (num - 1), mode);

        // 回覆舊主題？
        if (topic_id)
        {
                if (! BOARD_D->reply_topic(ob, topic_id,
                                           query("id", me), text,
                                           query_ip_number(me)))
                        tell_object(me, "回覆失敗，請向巫師查詢原因。\n");
                else
                        tell_object(me, "回覆完畢。\n");
                return;
        }

        // 發表新主題？
        if (! BOARD_D->post_new_topic(ob, title,
                                      query("id", me), text,
                                      query_ip_number(me)))
        {
                tell_object(me, "發表失敗，請向巫師查詢原因。\n");
                return;
        }

        tell_object(me, "發表完畢。\n");
        return;
}

int do_post(string arg, int n)
{
        object me;

        if (! arg)
                return notify_fail("發表文章請指定一個標題。\n");

        me = this_player();
        if (wiz_level(me) < 1)
        {
                if (query("mud_age", me) < 1800)
                        return notify_fail("你必須在完成註冊三十分鐘以後才能使用討論版，這段"
                                           "時間內請先閲讀他人的留言。\n");

                if (query("jing", me) < 50)
                        return notify_fail("你現在精神不濟，休息一會兒再説吧。\n");

                me->receive_damage("jing", 50);
        }

        if (replace_string(arg, " ", "") == "")
                arg = "無標題";

        me->edit((: done_post, me, arg :));
        return 1;
}

int do_read(string arg)
{
        object me, ob;
        int num, t, mode, time, max;
        mapping last_read_time;
        mixed *notes, *replies, *reply;
        mixed *pinfo, *tinfo;
        string myid, msg, title;

        me = this_player();
        ob = this_object();
        last_read_time = query("board_last_read", me);
        myid = query("board_id");
        // 是否使用 bbs 模式？
        mode = is_bbs_mode(me);

        if (! arg) return notify_fail("指令格式：read <文章 / 主題編號> | new | next\n");

        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        // 獲得本版所有留言
        notes = (mode ? BOARD_D->query_all_posts(ob)
                      : BOARD_D->query_all_topics(ob));
        time = (mode ? POST_TIME : TOPIC_TIME);

        if (! sizeof(notes)) return notify_fail("討論板上沒有任何文章。\n");

        if (arg == "new" || arg == "next")
        {
                if (! mapp(last_read_time) || undefinedp(last_read_time[myid]))
                        num = 1;
                else
                {
                        max = sizeof(notes);
                        for (num = 1; num <= max; num++)
                        {
                                if (notes[num - 1][time] > last_read_time[myid])
                                        break;
                        }
                }
        } else
        if (! sscanf(arg, "%d", num))
                return notify_fail("你要讀第幾篇文章？\n");

        if (num < 1 || num > sizeof(notes))
                return notify_fail("沒有這篇文章。\n");
        num--;

        // bbs 模式
        if (mode)
        {
                // 本帖相關的一些信息
                pinfo = BOARD_D->query_post_info(notes[num][POST_ID]);
                // 發貼的時間
                t = notes[num][POST_TIME];
                tinfo = BOARD_D->query_topic_info(notes[num][TOPIC_ID]);
                title = ((sizeof(tinfo) && pinfo[POST_SUBJECT] == "") ? ("Re: " + tinfo[TOPIC_TITLE]) :
                        pinfo[POST_SUBJECT]);

                msg = sprintf("[" WHT "%3d" NOR "]" WHT " %-40s " NOR "(%s) [ " WHT "%s" NOR " ]\n"
                              "─────────────────────────────"
                              "────────\n" NOR "%s\n───────────"
                              "────────────────────[ " WHT "BBS 模式"
                              NOR " ]\n" NOR, num + 1,
                              title, ctime(t)[0..9],
                              BOARD_D->query_mud_name(notes[num][POSTER_ID]), pinfo[POST_TEXT]);

                BOARD_D->add_topic_view(notes[num][TOPIC_ID], 1);

                // 此貼是哪篇主題的回覆？
                if (sizeof(tinfo))
                        msg += sprintf("此貼是主題 " WHT "%s" NOR " (%d) 的%s。\nWeb 地址： " WHT "(%s)" NOR,
                                       tinfo[TOPIC_TITLE], BOARD_D->query_topic_number(ob, tinfo[TOPIC_ID]),
                                       (tinfo[TOPIC_FIRST_ID] == notes[num][POST_ID] ? "首貼" : "回覆"),
                                       sprintf(TOPIC_URL, tinfo[TOPIC_ID]));
        } else
        {
                pinfo = BOARD_D->query_post_info(notes[num][TOPIC_FIRST_ID]);
                t = notes[num][TOPIC_TIME];

//              DEBUG_MSG(sprintf(HIC "notes[num] = " WHT "%O\n" NOR, notes[num]));
//              DEBUG_MSG(sprintf(HIC "pinfo = " WHT "%O\n" NOR, pinfo));

                msg = sprintf("[" WHT "%3d" NOR "]" WHT " %-40s " NOR "(%s) [ " WHT "%s" NOR " ]\n"
                              "─────────────────────────────"
                              "────────\n" NOR "%s\n───────────"
                              "────────────────────[ " WHT "Web 模式"
                              NOR " ]\nWeb 地址：" WHT "(%s)" NOR, num + 1,
                              notes[num][TOPIC_TITLE], ctime(t)[0..9],
                              BOARD_D->query_mud_name(notes[num][TOPIC_POSTER]), pinfo[POST_TEXT],
                              sprintf(TOPIC_URL, notes[num][TOPIC_ID]));

                BOARD_D->add_topic_view(notes[num][TOPIC_ID], 1);

                // 是否有回覆呢？
                if (notes[num][TOPIC_REPLIES])
                {
                        mode = query("env/reply_mode", me);

                        if (mode)
                        {
                                replies = BOARD_D->query_all_replies(notes[num][TOPIC_ID],
                                                                     notes[num][TOPIC_FIRST_ID]);
                                switch (mode)
                                {
                                // 顯示最後一篇回覆
                                case 1 :
                                        reply = replies[sizeof(replies) - 1];
                                        pinfo = BOARD_D->query_post_info(reply[POST_ID]);
                                        t = reply[POST_TIME];

                                        msg += sprintf(WHT "\nRe: %-42s "
                                                       NOR "(%s) [ " WHT "%s" NOR " ]\n"
                                                       "────────────────"
                                                       "────────────────"
                                                       "─────\n" NOR "%s\n" NOR,
                                                       notes[num][TOPIC_TITLE], ctime(t)[0..9],
                                                       BOARD_D->query_mud_name(reply[POSTER_ID]),
                                                       pinfo[POST_TEXT]);
                                        break;
                                // 顯示所有回覆
                                // case 2 :
                                default :
                                        foreach (reply in replies)
                                        {
                                                pinfo = BOARD_D->query_post_info(reply[POST_ID]);
                                                t = reply[POST_TIME];

                                                msg += sprintf(WHT "\nRe: %-42s "
                                                               NOR "(%s) [ " WHT "%s" NOR " ]\n"
                                                               "────────────────"
                                                               "────────────────"
                                                               "─────\n" NOR "%s\n" NOR,
                                                               notes[num][TOPIC_TITLE], ctime(t)[0..9],
                                                               BOARD_D->query_mud_name(reply[POSTER_ID]),
                                                               pinfo[POST_TEXT]);
                                        }
                                        break;
                                }
                                msg += "─────────────────────────────"
                                       "────────\n";
                        }
                        msg += "本主題共有 " WHT + notes[num][TOPIC_REPLIES] + NOR " 篇回覆。\n";
                }
        }
        me->start_more(msg);

        // 記錄上次閲讀到哪裏
        if (! mapp(last_read_time))
                set("board_last_read", ([myid:t]), me);
        else
                if (undefinedp(last_read_time[myid]) || t > last_read_time[myid])
                        last_read_time[myid] = t;
        return 1;
}

int do_discard(string arg)
{
        mixed *pdata;
        mixed *tinfo;
        int num;
        int mode;
        int topic_id;
        int post_id;
        object me;
        object ob;

        me = this_player();
        ob = this_object();

        if (! arg || sscanf(arg, "%d", num) != 1)
                return notify_fail("指令格式：discard <留言編號>\n");

        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();

        mode = is_bbs_mode(me);
        if (mode)
        {
                post_id = BOARD_D->query_number_post(ob, num - 1);
                if (! post_id)
                        return notify_fail("沒有這篇文章。\n");

                pdata = BOARD_D->query_post_data(post_id);

                if (BOARD_D->query_user_name(pdata[POSTER_ID]) != query("id", me) &&
                    wiz_level(me) < wiz_level("(wizard)"))
                        return notify_fail("這篇文章不是你寫的，你也沒有刪除文章的權限。\n");

                BOARD_D->delete_post(ob, post_id);
                write("刪除第 " + num + " 篇文章....Ok。\n");
                return 1;
        } else
        {
                topic_id = BOARD_D->query_number_topic(ob, num - 1, mode);
                if (! topic_id)
                        return notify_fail("沒有這篇文章。\n");

                tinfo = BOARD_D->query_topic_info(topic_id);

                if (BOARD_D->query_user_name(tinfo[TOPIC_POSTER]) != query("id", me) &&
                    wiz_level(me) < wiz_level("(wizard)"))
                        return notify_fail("這篇文章不是你寫的，你也沒有刪除文章的權限。\n");

                BOARD_D->delete_topic(ob, topic_id);
                write("刪除第 " + num + " 篇主題....Ok。\n");
                return 1;
        }
}