// kuangfeng.c

#include <ansi.h>
inherit NPC;

#define WARCRAFT_OB             "/clone/npc/warcraft.c"
#define WARCRAFT_DIR            "/data/warcraft/"
#define CRUISE_OB               "/clone/misc/qiankun_ob.c"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_warcraft(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);

string* warcraft_type = ({
        "青龍",
        "白虎",
        "朱雀",
        "玄武",
        "麒麟",
});

mapping magic_type = ([ 
        "青龍" : "wood",
        "白虎" : "metal",
        "朱雀" : "fire",
        "玄武" : "water",
        "麒麟" : "earth",
]);

void create()
{
        set_name("狂風", ({ "kuang feng", "kuang", "feng" }) );
        set("gender", "男性" );
        set("age", 21);
        set("long",@LONG
狂風來自神祕的精意山莊，最近突然出現在揚州城，並出售
人們從沒有見過的魔幻獸，傳説這個魔幻獸具有神奇的功能，
你如果喜歡的話，不妨也選(choose)一隻。
LONG );
        set("title",HIW"煉器師"NOR);
        set("combat_exp", 5000000);

        set("inquiry", ([
                "魔幻獸"     : "只要給我一兩黃金，你就能擁有魔幻獸了！",
                "如意乾坤袋" : "給我材料地藏之石，你就可以擁有如意乾坤袋了。",
                "乾坤袋" : "給我材料地藏之石，你就可以擁有如意乾坤袋了。",
        ]));

        set_skill("training", 600);
        set_skill("huisheng-jue", 600);
        set("chat_chance", 15);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        create_family("精意山莊", 2, "弟子");
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_choose", "choose");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "狂風説道：這位" + RANK_D->query_respect(ob)
                                + "，要魔幻獸麼？\n");
                        break;
                case 1:
                        say( "狂風説道：這位" + RANK_D->query_respect(ob)
                                + "，魔幻獸可以保護主人的哦。\n");
                        break;
        }
}

int do_choose()
{
        object warcraft;
        string filename;
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");

        filename = WARCRAFT_DIR+query("id", me);
        if (file_size(WARCRAFT_DIR+query("id", me)+FILE_EXTENSION) > 0)
        {
                catch(call_other(filename, "???"));
                warcraft = find_object(filename);
                set("can_whistle/"+query("id", warcraft), filename, me);
                set("warcraft/id", query("id", warcraft), me);
                set("warcraft/file", filename, me);
                set("warcraft/status", "living", me);
                MYGIFT_D->check_mygift(me, "newbie_mygift/warcraft"); 
                return notify_fail("你宿命中已經擁有過魔幻獸，我已經幫你溝通血契了。\n");
        }

        if (me->query_skill("training", 1) <30)
                return notify_fail("你的馭獸術太低了，即使養了魔幻獸，也會背棄你而去。\n");

        if( !query_temp("warcraft/money", me) )
        {
                command("say 這位" + RANK_D->query_respect(me) + "，每隻魔幻獸一百兩黃金，你必須先給錢！");
                return 1;
        }

        write("您要養哪類魔幻獸：\n");
        write(" 1. 青龍   2. 白虎   3. 朱雀   4. 玄武  5. 麒麟\n");
        write("請選擇數字代號：(q 鍵取消)");

        input_to( (: get_subtype :), me);
        return 1;
}

void get_subtype(string arg, object ob)
{
        int n;

        if (arg == "q" || arg == "Q")
                return;

        sscanf(arg, "%d", n);

        if (n <= 0 || n > 5)
        {
                write("您要養哪類魔幻獸：\n");
                write(" 1. 青龍   2. 白虎   3. 朱雀   4. 玄武  5. 麒麟\n");
                write("請選擇數字代號：(q 鍵取消)");
                input_to( (: get_subtype :), ob);
                return;
        }
        set_temp("warcraft/race_type", warcraft_type[n-1], ob);

        write("\n");
        write("請設定魔幻獸的性別(雄性：1  雌性：0)：");
        input_to( (: get_gender :), ob );
}

void get_gender(string arg, object ob)
{
        int n;
        object warcraft;

        sscanf(arg, "%d", n);

        if (n != 0 && n != 1)
        {
                write("\n");
                write("請設定魔幻獸的性別(雄性：1  雌性：0)：");
                input_to( (: get_gender :), ob );
                return;
        }
        set_temp("warcraft/gender", n?"男性":"女性", ob);

        write("\n");

        write(sort_string(CYN "你按照狂風的指點開始飛快的念道：“在天的見"
                "證之下，集勇氣、智慧、與美麗於一身的強大生物，幻獸呀！請"
                "你以最深的靈性，聆聽我的傾訴，我－"+query("name", ob)+
                "－將與你締結永生的血之盟約，終此生惟有你與我為終生之盟友"
                "，契。”\n" NOR, 64));
        write("你與魔幻獸的血之盟約簽訂完畢。\n");
        write("請設定魔幻獸的英文 id ：");
        input_to( (: get_id :), ob );
}

void get_id(string arg, object ob)
{
        arg = lower_case(arg);

        if (! check_legal_id(arg))
        {
                write("\n");

                write("請設定魔幻獸的英文 id ：");
                input_to( (: get_id :), ob );
                return;
        }

        arg = replace_string(arg, " ", "_");

        set_temp("warcraft/id", arg, ob);

        write("\n");
        write("請設定魔幻獸的中文名：(可加顏色help nick)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        string  result;

        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg_old = arg;

        arg = trans_color(arg, 3);
        arg = filter_color(arg);

        if (! check_legal_name(arg, 12))
        {
                write("請設定魔幻獸的中文名：(可加顏色)");
                input_to( (: get_name :), ob);
                return;
        }

        if (stringp(result = NAME_D->invalid_new_name(arg)))
        {
                write("對不起，" + result);
                write(HIR "禁止使用與他人姓名相同或接近的魔幻獸名。並因循RULES中對名字的相關規定。"NOR+"\n");
                input_to( (: get_name :), ob);
                return;
        }

        arg = arg_old;
        arg = trans_color(arg, 3);

        set_temp("warcraft/name", arg, ob);

        write("\n");
        write("請描述魔幻獸：(不可加顏色)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        if (! check_legal_name(arg, 60))
        {
                write("請描述魔幻獸：");
                input_to( (: get_desc :), ob);
                return;
        }

        set_temp("warcraft/desc", arg, ob);
        write("ok\n");
        build_warcraft(ob);
}

void build_warcraft(object ob)
{
        string file, filename;
        object warcraft, money;
        string warcraft_id;
        string warcraft_name;
        string warcraft_type;
        string warcraft_desc;
        string warcraft_gender;

        warcraft_id=query_temp("warcraft/id", ob);
        warcraft_name=query_temp("warcraft/name", ob);
        warcraft_name += NOR;

        warcraft_desc=query_temp("warcraft/desc", ob);
        warcraft_desc += NOR;
        warcraft_gender=query_temp("warcraft/gender", ob);
        warcraft_type = query_temp("warcraft/race_type", ob);

        file = read_file(WARCRAFT_OB);

        file = replace_string(file, "WARCRAFT_NAME", warcraft_name);
        file = replace_string(file, "WARCRAFT_ID", warcraft_id);
        file = replace_string(file, "WARCRAFT_GENDER", warcraft_gender);
        file = replace_string(file, "RACE_TYPE", warcraft_type);
        file = replace_string(file, "MAGIC_TYPE", magic_type[warcraft_type]);
        file = replace_string(file, "LONG_DESCRIPTION",
                            warcraft_desc + "\n" + "它是" +
                            query("name", ob)+"的魔幻獸。\n");

        file=replace_string(file,"OWNER_ID",query("id", ob));
        file=replace_string(file,"OWNER_NAME",query("name", ob));

        filename=WARCRAFT_DIR+query("id", ob);
        if (file_size(filename + ".c") > 0)
        {
                if (warcraft = find_object(filename))
                        destruct(warcraft);
                DBASE_D->clear_object(filename);
                rm(filename + ".c");
        }

        assure_file(filename);
        write_file(filename + ".c", file); // 寫入文件
        VERSION_D->append_sn(filename + ".c"); // 給物品增加識別碼

        catch(call_other(filename, "???"));
        warcraft = find_object(filename);
        if (! warcraft)
        {
                delete_temp("warcraft", ob);
                money = new("/clone/money/gold");
                money->set_amount(100);
                money->move(ob, 1);
                message_vision("$N一呆，對$n道：抱歉抱歉！出了一些問題！錢我還是還你吧。\n",
                               this_object(), ob);
                return;
        }
        set("level", 1, warcraft);

#ifdef DB_SAVE
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_remove_item(filename);
        DATABASE_D->db_create_item(warcraft, warcraft->query_entire_dbase());
#endif
        warcraft->save();
        destruct(warcraft);

        set("can_whistle/"+warcraft_id, filename, ob);
        set("warcraft/id", warcraft_id, ob);
        set("warcraft/file", filename, ob);
        set("warcraft/status", "living", ob);
        delete_temp("warcraft", ob);

        command("say 你可以吹聲口哨召喚你的魔幻獸！<whistle " + warcraft_id +">\n");

        MYGIFT_D->check_mygift(ob, "newbie_mygift/warcraft");   
        return;
}

int accept_object(object me, object ob)
{
        string filename;
        string file;
        object cruise_ob, xob;

        if( query("id", ob) == "dizang zhishi" )
        {
                filename=ITEM_DIR+"cruise/"+query("id", me);
                if (file_size(filename + ".c") > 0)
                {
                        message_vision("$N一呆，對$n道：你的宿命中已經擁有過如意乾坤袋！我幫你恢復了。\n",
                                       this_object(), me);
                        set("can_summon/qiankun", filename, me);
                        return 0;
                }

                command("say 這可是製作如意乾坤袋的特殊材料，既然你我有緣，我就免費幫你製作一個吧！");
                if (1)
                {
                        file = read_file(CRUISE_OB);
                        file = replace_string(file, "LONG_DESCRIPTION",
                                                "這是" + me->query_idname(1) + "的如意乾坤袋。\n");

                        // give cruise ob to me
                        filename=ITEM_DIR+"cruise/"+query("id", me);
                        if (file_size(filename + ".c") > 0)
                        {
                                if (cruise_ob = find_object(filename))
                                        destruct(cruise_ob);

                                DBASE_D->clear_object(filename);
                                rm(filename + ".c");
                                //log_file("cruise_ob",sprintf("%s have new cruise ob.\n",query("id", me)));
                        }
                        assure_file(filename);
                        write_file(filename + ".c", file);
                        VERSION_D->append_sn(filename + ".c");

                        catch(call_other(filename, "???"));
                        cruise_ob = find_object(filename);
                        if (! cruise_ob)
                        {
                                delete_temp("make_cruise_ob", me);
/*
                                xob = new("/clone/item/dizangshi");
                                xob->move(me, 1);
*/
                                message_vision("$N一呆，對$n道：抱歉抱歉！出了一些問題！材料我還是還你吧。\n",
                                               this_object(), me);
                                return 0;
                        }
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_remove_item(filename);
                        DATABASE_D->db_create_item(cruise_ob, cruise_ob->query_entire_dbase());
#endif

                        cruise_ob->move(me, 1);
                        cruise_ob->save();
                        set("can_summon/qiankun", filename, me);
                        delete_temp("make_cruise_ob", me);
                        tell_object(me, HIY "你獲得了一個如意乾坤袋。\n" NOR);
                        destruct(ob);
                        return 1;
                }
        }

        if( query("money_id", ob) )
        {
                if (ob->value() < 10000)
                {
                        command("say 這位給的未免少了點！每隻魔幻獸要一兩黃金！");
                        return 0;
                }

                if (me->query_skill("training", 1) < 30)
                {
                        command("say 你的馭獸術不夠，即使養了魔幻獸，也會離你而去！");
                        return 0;
                }
                else
                {
                        set_temp("warcraft/money", 1, me);
                        command("say 好我收下了！");
                        command("say " + me->name() +
                                     "，現在我這裏有各種魔幻獸！");
                        command("say 請選擇你要的魔幻獸 < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}

int check_legal_id(string id)
{
        int i;
        string *legalid;
        object ppl;

        i = strlen(id);

        if ((strlen(id) < 3) || (strlen(id) > 20))
        {
                write("對不起，英文 id 必須是 3 到 20 個英文字母。\n");
                return 0;
        }

        while(i--)

        if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))
        {
                write("對不起，英文 id 只能用英文字母。\n");
                return 0;
        }

        ppl = LOGIN_D->find_body(id);

        if (ppl || id == "guest" || id == "new")
        {
                write("這個名字與別的玩家ID相同了．．．");
                return 0;
        }

        if (file_size(sprintf("/data/user/%c/%s", id[0], id)
                    + __SAVE_EXTENSION__) >= 0)
        {
                write("這個名字已經被別的玩家使用了．．．");
                return 0;
        }

        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("對不起，魔幻獸中文字必須是 1 到 %d 箇中文字。\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 13 && ! is_chinese(name))
        {
                write("對不起，請您用「中文」為寵物取名字或描述。\n");
                return 0;
        }
        return 1;
}

int attempt_apprentice(object ob)
{
        command("say 滾！給我一邊兒去！");
}

int recognize_apprentice(object me, string skill)
{
        if (skill == "training" || skill == "huisheng-jue")
                return 1;
        else
                return 0;
}
