// 客棧類工作守護：kezhan.c

// Updated by Lonely



// 獲准工作(老闆)

//     |

// 分配工作(小二) -+- 掃地 ----+

//                 |           +-- 工作過程 -- 完成 +

//                 +- 洗盤子 --+                    |

//                                 領取獎勵(小二) --+



#include <ansi.h>



#define NAME            "kezhan"        // 工作名稱

#define BONUS           10 + random(30) // 獎勵基數

#define MAX_NUM         20              // 最多人數，為 0 時不檢查

#define MIN_EXP         0               // 最少經驗

#define MAX_EXP         100000          // 最多經驗，為 0 時不檢查



// 提供的外部函數

public int    query_work(object me);

public int    request_work(object me, object ob);

public int    start_work(object me);

public int    finish_work(object me, object ob, object obj);

public string assign_work(object me);



// 工作對象創建

void create() { seteuid(getuid()); }



private int fail_msg(string arg) 

{ 

        write(arg);

        return 1; 

}



private string query_zone(object arg)

{

        string zone;

        

        if (sscanf(file_name(arg), "/d/%s/%*s", zone) == 2)

                return zone;

        return "work";

}



// 查詢 me 的任務狀態

public int query_work(object me) { return me->query_temp("work/" + NAME + "/state"); }



// 請求任務，me 為請求者，ob 為被請求者

public int request_work(object me, object ob)

{

        // 分派工作者的檢查

        if (playerp(ob) || ob->query("work/name") != NAME)

                return fail_msg(ob->name() + "望着你呵呵傻笑。\n");



        if (MAX_NUM > 0 && ob->query("work/working") >= MAX_NUM)

                return fail_msg(ob->name() + "一皺眉道：“現在我們"

                                "這裏不缺人手，你等人少的時候再來吧"

                                "。”\n");

        // 接受工作者的檢查

        if (ob->query("combat_exp") < MIN_EXP)

                return fail_msg(ob->name() + "瞥了" + me->name() +

                                "一眼道：“就憑你也幹得了咱這工作？"

                                "”\n");

        if (MAX_EXP > 0 && me->query("combat_exp") > MAX_EXP && ! wizardp(me))

                return fail_msg(ob->name() + "滿臉堆笑道：“這點小"

                                "事就不敢麻煩大俠您了。”\n");



        switch(query_work(me))

        {

        // 0 為不在做此工作

        case 0:

                message_vision(CYN "$N" NOR CYN "一點頭對$n" NOR CYN 

                               "道：“嗯，好吧，你去廚房看看有什麼工作"

                               "可做的。”\n", ob, me);

                // 設定玩家做此工作的狀態

                me->set_temp("work/" + NAME + "/state", 1);

                me->set_temp("work/" + NAME + "/zone", query_zone(environment(ob)));



                break;

        // 1 為許可了，尚未正式開始工作

        case 1:

                message_vision(CYN "$N" NOR CYN "疑惑的對$n" NOR CYN

                               "道：“咦，你不是已經領了工作麼？還不快"

                               "去？”\n", ob, me);

                break;

        // 2 為正在進行工作

        case 2:

                message_vision(CYN "$N" NOR CYN "皺着眉頭對$n" NOR CYN

                               "道：“你不是正在做事嘛？快回去，做完再"

                               "來我這領獎勵。”\n", ob, me);

                break;

        // 3 為工作過程已經完成，正獲取獎勵

        case 3:

                message_vision(CYN "$N" NOR CYN "用毛巾抹了抹手，對$n"

                               NOR CYN "道：“掌櫃的，我的事兒做完了，"

                               "您......”\n", me, ob);

                finish_work(me, ob, 0);

                break;

        default:

                return 0;

        }

        return 1;

}



// 按照狀態分配一個具體的工作分支，並返回這個工作分支的描述信息

public string assign_work(object me)

{

        string msg;

        int i;

        object dish, besom;



        switch (random(2))

        {

        // 洗盤子

        case 0:

                i = 2 + random(3);

                dish = new("/clone/work/dish");

                dish->set_amount(i);

                dish->move(me);

                msg = "喏，這裏有" + chinese_number(i) + "個盤子(dish)，"

                      "快幫我洗洗(wash)，急着用呢。";

                me->set_temp("work/" + NAME + "/type", "wash");

                me->set_temp("work/" + NAME + "/wash", i);

                break;

        // 掃地

        case 1:

                besom = new("/clone/work/besom");

                besom->move(me);

                msg = "唔，這裏的地(floor)也夠髒的了，你把這裏四周給掃掃"

                      "(sweep)，手腳麻利些。";

                me->set_temp("work/" + NAME + "/type", "sweep");

                break;

        }

        me->set_temp("work/" + NAME + "/state", 2);

        return msg;

}



// 開始工作，根據玩家身上的設定決定工作類型

public int start_work(object me)

{

        string type;

        object ob;

        array place;



        if (! mapp(me->query_temp("work/" + NAME)))

                return fail_msg("你現在並沒有領到工作呀，瞎折騰個啥呢"

                                "。\n");

        

        if (! stringp(type = me->query_temp("work/" + NAME + "/type")) ||

            type != "wash" && type != "sweep")

                return fail_msg("似乎什麼地方出了一點問題，你並沒有被"

                                "分配到具體的工作類型。\n");



        if (me->is_busy())

                return fail_msg("你忙完手裏的事情再工作吧。\n");



        switch (type)

        {

        case "wash":

                if (! objectp(ob = present("dirty dish", me)))

                        return fail_msg("你的身上已經沒有髒盤子了。\n");



                if (! environment(me)->query("resource/water"))

                        return fail_msg("這裏沒有水，怎麼洗呢？\n");



                if (me->query("qi") < 30 || me->query("eff_qi") < 50 ||

                    me->query("jing") < 20 || me->query("eff_jing") < 50)

                        return fail_msg("你先歇歇再洗吧，可別洗盤子洗出"

                                        "人命來。\n");



                me->set_temp("work/" + NAME + "/step", 1);

                me->start_busy(bind((: call_other, __FILE__, "continue_working" :), me),

                               bind((: call_other, __FILE__, "halt_working" :), me));



                tell_object(me, "你開始工作。\n");

                return 1;

                

        case "sweep":

                if (! objectp(ob = present("besom", me)))

                        return fail_msg("你的身上都沒有掃把，怎麼掃？\n");



                // 只能在客棧掃地

                if (! environment(me)->query("hotel") ||

                    me->query_temp("work/" + NAME + "/zone") != query_zone(environment(me)))

                        return fail_msg("這裏可不是店小二叫你掃的地方呀。\n");



                if (arrayp(place = me->query_temp("work/" + NAME + "/place")) &&

                    member_array(file_name(environment(me)), place) != -1)

                        return fail_msg("這個地方你已經掃過了，不必再重複一次。\n");



                if (me->query("qi") < 30 || me->query("eff_qi") < 30 ||

                    me->query("jing") < 20 || me->query("eff_jing") < 30)

                        return fail_msg("你先歇歇再掃吧，可別掃地洗出人命來。\n");



                me->set_temp("work/" + NAME + "/step", 1);

                me->start_busy(bind((: call_other, __FILE__, "continue_working" :), me),

                               bind((: call_other, __FILE__, "halt_working" :), me));



                tell_object(me, "你開始工作。\n");

                return 1;

        }

        return 0;

}



// 正在工作

int continue_working(object me)

{

        string msg;

        int finish;

        int b;



        if (! me->query_temp("work/" + NAME + "/step"))

                me->set_temp("work/" + NAME + "/step", 1);



        if (! living(me))

        {

                me->delete_temp("work/" + NAME + "/step");

                return 0;

        }



        finish = 0;

        me->receive_damage("jing", 1);

        me->receive_damage("qi", 2);

        

        switch (me->query_temp("work/" + NAME + "/type"))

        {

        case "wash":

                switch (me->query_temp("work/" + NAME + "/step"))

                {

                case 1:

                        msg = "$N抓起一個髒盤子，浸入水盆。";

                        break;

                case 2:

                        msg = "$N往盆子裏倒了一些皂角液。";

                        break;

                case 3:

                        msg = "$N左手捏着盤子，右手拿着抹布，開始擦抹。";

                        break;

                case 4:

                case 6:

                        msg = "$N小心翼翼的擦抹盤子。";

                        break;

                case 5:

                        msg = "$N給抹布蘸了點水，繼續仔細地洗盤子。";

                        break;

                case 7:

                        msg = "$N不斷擦抹着盤子，盤子上的污垢漸漸除去。";

                        break;

                default:

                        msg = "$N洗好以後，將盤子透幹，用抹布一抹，放在旁邊晾乾。";

                        finish = 1;

                        break;

                }

                break;

        case "sweep":

                switch (me->query_temp("work/" + NAME + "/step"))

                {

                case 1:

                        msg = "$N抓起手邊的掃把，戴上袖套。";

                        break;

                case 2:

                        msg = "$N往地上灑了點水。";

                        break;

                case 3:

                        msg = "$N費力的揮動掃把，開始打掃地上的垃圾。";

                        break;

                case 4:

                case 6:

                        msg = "$N埋頭清掃地上的灰塵。";

                        break;

                case 5:

                        msg = "$N剷起腳邊的垃圾，繼續仔細地掃地。";

                        break;

                case 7:

                        msg = "$N不斷掃拭着地面，地面漸漸變得光可鑑人。";

                        break;

                default:

                        msg = "$N掃好以後，將所有的垃圾鏟進籮筐，放下掃把。";

                        finish = 1;

                        break;

                }

                break;

        }

        msg += "\n";



        if (finish)

        {

                object dish, cdish;



                me->delete_temp("work/" + NAME + "/step");



                b = BONUS;

                // 獎勵修正

                if (me->query("combat_exp") > 200000)

                {

                        // 經驗太高，削弱獎勵

                        b = b / 2 + 1;

                        if (me->query("combat_exp") > 400000)

                        {

                                // 再次削弱獎勵

                                b = b / 2 + 1;

                        }

                }

                me->add("combat_exp", b);

                me->improve_potential((b + 2) / 3);



                if (me->query_temp("work/" + NAME + "/type") == "wash")

                {

                        if (objectp(dish = present("dirty dish", me)))

                        {

                                dish->add_amount(-1);

                                me->add_temp("work/" + NAME + "/washed", 1);

                                if (! objectp(cdish = present("clear dish", me)))

                                {

                                        cdish = new("/clone/work/cdish");

                                        cdish->move(me);

                                }

                                else 

                                        cdish->add_amount(1);

                        }

                        // 洗完了所有的盤子

                        if (me->query_temp("work/" + NAME + "/washed") ==

                            me->query_temp("work/" + NAME + "/wash"))

                                me->set_temp("work/" + NAME + "/state", 3);

                        msg += "你洗好了一個乾淨的盤子。\n";

                }

                else

                {

                        me->add_temp("work/" + NAME + "/place",

                                    ({ file_name(environment(me)) }));

                        me->set_temp("work/" + NAME + "/state", 3);

                        msg += "你把這個地方掃乾淨了。\n";

                }

        }



        msg = replace_string(msg, "$N", "你");

        tell_object(me, msg);



        if (finish)

        {

                if (b > 0)

                {

                        tell_object(me, HIC "\n你獲得了" +

                                    chinese_number(b) +

                                    "點經驗和" +

                                    chinese_number((b + 2) / 3) +

                                    "點潛能。\n\n" NOR);

                }

                return 0;

        }



        me->add_temp("work/" + NAME + "/step", 1);

        return 1;

}



// 中途停止工作

int halt_working(object me)

{

        if (me->query_temp("work/" + NAME + "/type") == "wash")

                message_vision("$N把手中的抹布盤子丟到一旁，抹了抹汗道："

                               "太累了太累了，歇歇再幹。\n", me);

        else

                message_vision("$N停下手，靠在身邊的掃把上，抹了抹汗道："

                               "太累了太累了，歇歇再幹。\n", me);



        me->delete_temp("work/" + NAME + "/step");

        return 1;

}



// 結束工作，領取獎勵

public int finish_work(object me, object ob, object obj)

{

        mapping m;

        object coin;



        if (! objectp(obj) || environment(obj) != me)

                return fail_msg(ob->name() + "點點頭道：“幹完了？那就"

                                "快把工具還給店小二去呀。”\n");



        if (! (m = me->query_temp("work"))) 

                return 0;

        

        if (! mapp(m) || m[NAME]["state"] != 3)

        {

                write(CYN + ob->name() + "疑惑道：“你還沒幹完呢，就來"

                      "要獎勵？”\n" NOR);

                return 0;

        }



        switch (m[NAME]["type"])

        {

        case "wash":

                if (obj->query("id") != "dish")

                {

                        write(CYN + ob->name() + "掃了一眼" + obj->name() +

                              "道：“這是我叫你洗的盤子？”\n" NOR);

                        return 0;

                }

                if (obj->query_amount() != m[NAME]["wash"])

                {

                        write(CYN + ob->name() + "數了數" + obj->name() +

                              "道：“這盤子的數目不對呀，給你打碎了？”\n" NOR);

                        return 0;

                }

                // 金錢報酬

                write(sort_msg(CYN + ob->name() + "看了看" + obj->name() +

                               "，點點頭道：“嗯，還不錯，這裏是你的工錢，"

                               "收好了。”\n" NOR));

                coin = new("/clone/money/coin");

                coin->set_amount(BONUS * m[NAME]["wash"] * 2);

                coin->move(me, 1);

                break;



        case "sweep":

                if (obj->query("id") != "besom")

                {

                        write(CYN + ob->name() + "掃了一眼" + obj->name() +

                              "道：“這是我給你的掃把？”\n" NOR);

                        return 0;

                }

                if (! arrayp(m[NAME]["place"]) || ! sizeof(m[NAME]["place"]))

                {

                        write(CYN + ob->name() + "瞪大眼睛望着你道：“你哪"

                              "裏也沒掃呀？”\n" NOR);

                        return 0;

                }

                // 金錢報酬

                write(sort_msg(CYN + ob->name() + "收起" + obj->name() +

                               "，點點頭道：“嗯，還不錯，這裏是你的工錢，"

                               "收好了。”\n" NOR));

                coin = new("/clone/money/coin");

                coin->set_amount(BONUS * sizeof(m[NAME]["place"]) * 2);

                coin->move(me, 1);

                break;



        default:

                write(CYN + ob->name() + "抓了抓腦袋道：“你乾的這是什"

                      "麼呢？我怎麼不知道呀。”\n" NOR);

                return 0;

        }

        // 清除工作的信息

        me->delete_temp("work");

        return 1;

}



mixed *query_info() { return ({ NAME, BONUS, MAX_NUM, MIN_EXP, MAX_EXP }); }

