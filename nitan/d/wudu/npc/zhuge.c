inherit NPC;
mixed ask_me();
#include <ansi.h>

void create()
{
        set_name("諸葛不亮", ({ "zhuge buliang", "zhuge", "buliang" }) );
        set("gender", "男性" );
        set("age", 35);
        set("per", 30);
        set("long", "一位羽扇綸巾，仙風道骨的文士。\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("literate", 200);

        set("chat_chance", 2);
        set("chat_msg",({
                CYN "諸葛不亮歎道：本人上知天文，下曉地理，有經天緯地之才，奈何無人知曉。\n" NOR,
                CYN "諸葛不亮道：要過桃花峪，非得我諸葛家主傳的諸葛行軍散不可。\n" NOR,
        }));
        setup();

        add_money("silver", 20);
        set("inquiry", ([
                "name"       : "在下乃諸葛武候之第二十三代孫諸葛不亮是也。\n",
                "here"       : "此乃卧龍崗，乃我先祖讀書之地也。\n",
                "諸葛亮"     : "閣下怎好直呼我先祖名諱？\n",
                "孔明先生"   : "此乃吾之先祖也，曾七擒孟獲，平定了南疆。故而閣下若去\n"
                               "南疆，或許鄙人能助君一臂之力。",
                "瘴氣"       : (: ask_me :),
                "桃花峪"     : (: ask_me :),
                "諸葛行軍散" : (: ask_me :),
        ]));
        carry_object("/d/city/obj/cloth")->wear();
}

mixed ask_me()
{
        object ob;
        object me = this_player();

        if (present("xingjun san", me))
                return "嘿，這東西又賣不了錢，你要那麼多幹嘛？";

        command("say 苗疆桃花峪瘴氣險惡異常，但若帶有我先祖所創之諸葛行軍散當可無恙。");
        command("say 這包藥要隨身攜帶，切末離身啊，切記，切記！");
        ob = new(__DIR__"obj/xingjunsan");
        ob->move(me, 1);
        return 1;
}