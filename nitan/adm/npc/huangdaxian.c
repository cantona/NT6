#include <ansi.h>

inherit NPC;

string *qian_type =
({
        "婚姻",
});

void create()
{
        set_name("黃大仙", ({ "huang daxian", "daxian", "huang" }) );
        set("gender", "男性" );
        set("age", 85);
        set("long","一位抽簽算命的老先生。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);

        set("inquiry", ([
                "求簽" : "哈哈哈哈，你也知道老夫？求簽要心誠，要不要試試(qiuqian)？",
                "解簽" : "這可是有違天意的啊！罷了，老夫年事已高，時日無多，你就把簽給老夫看看！",
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("do_qiuqian","qiuqian");
        add_action("do_answer","answer");
}

int do_qiuqian()
{
        object me,ob,qian;
        int i;
        string str;

        me = this_player();
        ob = this_object();

        if( !wizardp(me) && time()-query_temp("last_qiuqian", me)<1800 )
                return notify_fail("才求簽不久，又想求簽，你當這是遊戲啊？\n");

        if (present("zhu qian",me))
                return notify_fail("你身上不是有一根簽麼？好好琢磨琢磨吧。\n");

        command("look "+query("id", me));
        command("consider");

        qian = new("/clone/misc/qian");
        qian->csh_qianwen();
        set("owner", query("id", me), qian);

        if (!qian->move(me))
                return notify_fail("身上帶這麼多東西還來求簽，你當是趕集啊？\n");

        message_vision("$N將一個簽筒遞給$n，面色凝重的叮囑道：『記住，心誠則靈！』\n",ob,me);
        message_vision("$N微閉雙眼，默默禱告，隨後捧起簽筒疾搖片刻，一根簽掉了出來。\n",me);
        message_vision("$N趕緊放下簽筒，俯身把簽揀了起來，小心翼翼的收入懷中。\n",me);

        set_temp("last_qiuqian", time(), me);
        delete_temp("have_gived", me);
        delete_temp("can_answer", me);

        return 1;
}

int do_answer(string arg)
{
        object me,ob,obj;
        int i;
        string str,document,file;
        mapping qianwen;

        me = this_player();
        ob = this_object();

        if( !query_temp("can_answer", me) )
                return notify_fail("一邊去，來搗什麼亂！\n");

        if( !objectp(obj=query_temp("qian", me)) )
        {
                delete_temp("can_anser", me);
                delete_temp("qian", me);
                return notify_fail("一邊去，來搗什麼亂！\n");
        }

        if (!arg || member_array(arg,qian_type) == -1)
        {
                str = HIC "我這裡有很多種簽：" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "、";
                }
                str += "，你想求哪種簽？\n";
                tell_object(me, str);
                tell_object(me, "想好了就回答我！(answer 答案)\n");
                return 1;
        }

        qianwen=query("qianwen", obj);

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        document = read_file(file) + "\n";
        tell_object(me,this_object()->name() + "口中念念有詞：\n");
        command("walkby "+query("id", me));
        tell_object(me,HIM + qianwen["doc"] + "\n" + NOR);
        tell_object(me,this_object()->name() + "對你說道：" + HIW + qianwen["title"] + NOR + "乃" + HIR + qianwen["type"] + NOR + "。\n");
        str = "簽文含義你好好記著！\n";
        str += HIG + document + NOR;
        tell_object(me,str);
        tell_object(me,"你求的是" + HIW + arg + NOR + "，待老夫想想！\n");
        switch (arg)
        {
                case "婚姻":
                        str = qianwen["love_fate"];
                        break;
                default:
                        command("yi");
                        command("consider");
                        message_vision("$N盯著簽尋思良久，臉色癒發凝重，突然將簽塞回$n手中，卻是一言不發！\n",this_object(),me);
                        obj->move(me);
                        return 1;
                        break;
        }
        command("whisper "+query("id", me)+" about "+str);
        command("smile "+query("id", me));
        message_vision("$N將簽還給了$n。\n",this_object(),me);
        obj->move(me);

        delete_temp("can_answer", me);
        delete_temp("qian", me);

        return 1;
}

int accept_object(object me, object ob)
{
        int i;
        mapping qianwen;
        string str,document,file;

        if( query("money_id", ob) )
        {
                if( !query_temp("have_gived", me) )
                {
                        command("say 沒事給老夫錢幹嘛？當老夫是叫化子麼？");
                        return 0;
                }
                if( ob->value()<query_temp("have_gived", me) )
                {
                        command("say 就這點錢也來糊弄老夫？當老夫窮瘋了麼？");
                        return 0;
                }
                command("nod "+query("id", me));
                command("say 孺子可教也！且告知老夫你所求何事？");
                str = HIC "這簽可是有很多解法：" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "、";
                }
                str += "，你想求哪種簽？\n";
                tell_object(me,str);
                tell_object(me,"想好了就告訴老夫！(answer 答案)\n");
                set_temp("can_answer", 1, me);
                delete_temp("have_gived", me);
                addn("balance", ob->value(), this_object());
                destruct(ob);
                return -1;
        }

        if( query("id", ob) != "zhu qian" )
        {
                command("say 這是什麼東西？老夫要來何用？");
                return 0;
        }

        if( !mapp(qianwen=query("qianwen", ob)) || 
            query("owner", ob) != query("id", me) )
        {
                command("haha");
                command("say 你哪裡揀來一根牙簽，也好意思來糊弄我！");
                return 0;
        }

        if (undefinedp(qianwen["id"]) ||
            !intp(qianwen["id"]) ||
            undefinedp(qianwen["title"]) ||
            !stringp(qianwen["title"]) ||
            qianwen["title"] == "" )
        {
                command("yi");
                command("consider");
                message_vision("$N盯著簽尋思良久，臉色癒發凝重，突然將簽塞回$n手中，卻是一言不發！\n",this_object(),me);
                ob->move(me);
                return -1;
        }

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        if (file_size(file) < 0)
        {
                command("yi");
                command("consider");
                message_vision("$N盯著簽尋思良久，臉色癒發凝重，突然將簽塞回$n手中，卻是一言不發！\n",this_object(),me);
                ob->move(me);
                return -1;
        }

        switch (qianwen["type"])
        {
                case "上上簽":
                case "下下簽":
                        command("heihei");
                        tell_object(me,"這簽可是非同小可，老夫本也不應泄漏天機，如果你願意給我十兩黃金，尚可考慮！\n");
                        set_temp("have_gived", 100000, me);
                        break;
                default:
                        command("say");
                        tell_object(me,"這簽解答雖是容易，可找別人未必就能解正天意，若想明其究竟，你可願意給我黃金五兩？\n");
                        set_temp("have_gived", 50000, me);
                        break;
        }
        set_temp("qian", ob, me);
        return 1;
}

