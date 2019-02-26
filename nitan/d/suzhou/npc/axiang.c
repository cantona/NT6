// Last Modified by Winder on May. 15 2001
// axiang.c
inherit NPC;

int ask_letter();

void create()
{
        set_name("阿祥", ({ "nongfu" , "a xiang", "a", "xiang" }) );
        set("nickname", "農夫");
        set("gender", "男性" );
        set("age", 44);
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set("rank_info/respect", "農民伯伯");
        set("inquiry", ([
                "name"   : "俺叫阿祥，不過俺不是這裏土生土長的人。",
                "rumors" : "真懷念年輕時和阿根一起盜墓的時光呀。",
                "here"   : "這裏是曹娥江，你看到那塊碑了嗎？背後的文字是東漢蔡邕讀完碑文後寫的，不知道是什麼意思，好難理解呀！",
                "碑"     : "就在那邊呀，你不會沒看見吧？",
                "字"     : "蔡邕寫的那八個字嗎？自己看去！",
                "文字"   : "蔡邕寫的那八個字嗎？自己看去！",
                "阿根"   : "小時候的好夥伴了，我現在來到這裏，他卻還留在大理。",
                "鐵鏟"   : "嘿嘿，要鐵鏟做什麼？難不成你也想盜墓？",
                "盜墓"   : "那是以前乾的勾當啦。幹這種活需要好工具呀，普通的鐵鏟什麼的可不順手！",
                "工具"   : "我這裏沒有啦，阿根那裏可能還有。不過聽説他在大理當了大官，不會再幹這個了。如果我寫封信去，他也許還會賣我這個老臉。",
                "信"     : (: ask_letter :),
        ]) );
        setup();
}

void init()
{
        add_action("do_answer", ({"answer", "huida", "da"}));
        ::init();
}

int ask_letter()
{
        set_temp("axiang_letter", 1, this_player());
        say( "農夫説道：“要我寫信也成，不過你得先告訴(answer)我碑後面那八個字的意思。”\n");
        return 1;
}

int do_answer(string arg)
{
        object ob, me = this_player();
        int flag;

        if( !(flag=query_temp("axiang_letter", me)))return 0;
        if (!arg) return notify_fail("你要回答什麼？\n");
        if (arg == "絕妙好辭")
        {
                write( "你説道：“這不過是隱語罷了。‘黃絹’是顏色之絲，乃‘絕’字；‘幼婦’者，少女也，乃‘妙’字；‘外孫’，女之子，乃‘好’字；‘齏臼’，受五辛之器，是為‘辭’字。所以意思是‘絕妙好辭’。”\n");
                tell_room(environment(), me->name() + "對着農夫侃侃而談。\n", ({me}));
                if (flag == 2)
                {
                        command("kick"+query("id", me));
                        message_vision("$N罵道：“你不是説過一遍了嗎？怎麼又來羅嗦！”\n", this_object());
                }
                else
                {
                        message_vision("$N一拍大腿：“我怎麼沒有想到呀！”\n", this_object());
                        write("阿祥説：“好吧，我就寫封信給阿根。”\n");
                        set_temp("axiang_letter", 2, me);
                        ob = new(__DIR__"obj/axiang_xin");
                        ob->move(me);
                }
        }
        else
        {
                message_vision("$N道：“容易！不就是" + arg + "的意思嘛。”\n", me);
                command("laugh"+query("id", me));
                message_vision("農夫對$N説道：“我本以為自己是天底下最沒文化的，現在看來只能排第二了。”\n", me);
        }
        return 1;
}
