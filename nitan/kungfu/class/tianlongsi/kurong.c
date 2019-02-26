// This program is a part of NT MudLIB
// kurong.c

// 六脈神劍載體

#include <ansi.h>

#define SIX_BOOK "/clone/book/six_book"

inherit NPC;
inherit F_MASTER;


int ask_me();
void start_fight(object me);
void close_exit();
void open_exit();

string* names = ({
        "ben yin",
        "ben can",
        "ben chen",
        "ben guan",
        "ben xiang",
});

void create()
{
        set_name("枯榮大師", ({ "kurong", "ku"}) );
        set("gender", "男性" );
        set("title", "天龍寺第十六代僧人");
        set("class", "bonze");
        set("long", @LONG
他的面壁而坐，看不見面貌。
LONG );
        set("age", 95);
        set("shen_type", 1);
        set("str", 32);
        set("int", 34);
        set("con", 31);
        set("dex", 32);

        set("qi", 5500);
        set("max_qi", 5500);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 6700);
        set("max_neili", 6700);
        set("jiali", 120);
        set("level", 30);
        set("combat_exp", 2700000);

        set_skill("force", 300);
        set_skill("dodge", 280);
        set_skill("parry", 280);
        set_skill("finger", 280);
        set_skill("tiannan-bu", 280);
        set_skill("kurong-changong", 280);
        set_skill("kurong-changong", 300);
        set_skill("sun-finger", 280);
        set_skill("literate", 260);
        set_skill("buddhism", 2400);
        set_skill("lamaism", 2400);
        set_skill("martial-cognize", 220);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("parry", "sun-finger");
        map_skill("finger", "sun-finger");

        prepare_skill("finger","sun-finger");

        set("inquiry" ,([
                "六脈神劍" : (: ask_me :),
                "六脈神劍譜" : (: ask_me :),
                "六脈神劍劍譜" : (: ask_me :),
        ]));
        create_family("大理段家", 14, "高僧");

        set_temp("apply/damage", 50);
        set_temp("apply/armor", 50);

        setup();
        carry_object("/clone/cloth/seng-cloth")->wear();
}

int remove_killer(object ob)
{
        object env;

        ::remove_killer(ob);

        if (sizeof(query_killer())) return 1;

        env = environment();
        if( query("exits", env))return 1;

        message_vision("$N歎了一口氣，道：出家人豈能濫殺無"
                       "辜？然而降妖除魔，也是無法。\n",
                       this_object());

        open_exit();
        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("shen", ob)<-5000 )
                command("say 你雖魔性太重，但是佛門廣大，老衲奉勸施主以後還是多多向善。");

        if (skill == "literate")
        {
                command("say 抱歉，想學文化請去找教書先生。");
                return -1;
        }

        if (! query_skill(skill, 1))
        {
                command("say 嘿嘿，老僧不會，你另請高明吧。");
                return -1;
        }

        if (skill != "lamaism" && skill != "buddhism")
        {
                command("say 做人不要一味兇猛好殺，盡學一些"
                        "殺傷人命的武技。");
                return -1;
        }

        if( query_temp("mark/枯榮", ob) )
                return 1;

        command("nod");
        command("say 好，我就和你談談一些佛法方面的體會。");
        set_temp("mark/枯榮", 1, ob);
        return 1;
}

int ask_me()
{
        object me;

        me = this_player();
        if( query("born_family", me) != "段氏皇族" )
        {
                message_vision("$N冷笑一聲道：" +
                               RANK_D->query_respect(this_player()) +
                               "打聽我們天龍寺鎮寺之寶幹什麼？\n",
                               this_object());
                return 1;
        }

        message_vision("$N淡然對$n道：你雖然是皇族之人，但是也不"
                       "得染指六脈神劍劍譜。\n", this_object(), me);
        return 1;
}

int accept_fight(object ob)
{
        command("say 我沒有興趣陪你打架。");
        return 0;
}

int accept_hit(object ob)
{
        command("heng");
        command("command 你要找死麼？");
        start_fight(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("haha");
        command("say 來的好！咱們就較量一番！");
        start_fight(ob);
        return 1;
}

void start_fight(object me)
{
        object *obs, ob;
        string msg;
        int i;

        if (!living(this_object()))
                return;

        if (base_name(environment()) != query("startroom") ||
            is_killing(query("id", me)) )
        {
                command("say 那就打吧。");
                return;
        }

        if (is_fighting())
        {
                command("chat哈哈！"+query("name", me)+
                        "你這" + RANK_D->query_rude(me) +
                        "也來添亂？");
        } else
        {
                command("chat哼！好你個"+query("name", me)+
                        "，既然要挑我們天龍寺的百年威名，那"
                        "就來吧！");
        }

        obs = ({ });
        msg = 0;
        for (i = 0; i < sizeof(names); i++)
        {
                if (! objectp(ob = present(names[i])))
                        continue;

                if (! living(ob))
                        continue;

                obs += ({ ob });
                if (! msg)
                        msg = ob->name();
                else
                        msg += "、" + ob->name();
        }

        if (msg)
                command("say " + msg + "，大家一起把這賊子殺了！");
        else
                command("say 也罷，就由老僧我來超度你吧！");

        obs->kill_ob(me);
        kill_ob(me);
        close_exit();
        call_out("open_exit", 30);
}

varargs void die(object killer)
{
        object ob;
        if (! killer) killer = this_object()->query_last_damage_from();

        /*
        ob = find_object(SIX_BOOK);
        if (! objectp(ob))
                 ob = load_object(SIX_BOOK);


        */
        if (random(10) == 1)
        {
                ob = new(SIX_BOOK);
                ob->move(this_object(), 1);
                CHANNEL_D->do_channel(this_object(), "rumor", "聽説" +
                        (objectp(killer) ? killer->name(1) : "某人") +
                        "闖入天龍寺，力戰眾僧，奪走六脈神劍譜。");
        } else
                CHANNEL_D->do_channel(this_object(), "chat", "天哪！想不到我枯榮飽遭凌辱，天龍威名盡喪我手！");

        open_exit();
        ::die(killer);
}

void close_exit()
{
        object room;
        object here;

        here = environment();
        room = find_object("/d/tianlongsi/banruotai");
        if (! room) room = load_object("/d/tianlongsi/banruotai");

        if( !query("exits", here) )
                return;

        message_vision("$N劈空一掌，登時將大門閉上。\n", this_object());
        delete("exits", here);

        if (room)
        {
                message("vision", "忽然“砰”的一下" +
                        query("short", room)+"的大門閉上了。\n",room);
                delete("exits/south", room);
        }
}

void open_exit()
{
        object room;
        object here;

        here = environment();
        room = find_object("/d/tianlongsi/banruotai");
        if (! room) room = load_object("/d/tianlongsi/banruotai");

        if( query("exits", here) )
                return;

        message("vision", "大門“吱呀吱呀”的打開了。\n", here);
        set("exits/north", "/d/tianlongsi/banruotai", here);

        if (room)
        {
                message("vision","忽然"+query("short", room)+
                        "的大門“吱呀吱呀”的打開了。\n", room);
                set("exits/south", "/d/tianlongsi/munitang", room);
        }
}
