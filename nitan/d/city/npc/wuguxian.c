// wuguxian.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL "吳古賢" NOR,({ "wu guxian", "wu", "teacher"}) );
        set("title", "資政書院先生");
        set("gender", "男性" );
        set("age", 55);
        set("long", @LONG
吳古賢據說在資政學院已經教了十幾年的書，年紀也大了，變的越來越
迂腐，學問和年輕時差的遠了；又當今的大儒增先生開始授課，吳先生
的資政學院幾乎成了一些頑劣兒童的樂園。
LONG
        );
        set("attitude", "peaceful");
        set("combat_exp", 10);
        set("str", 15);
        set("con", 18);
        set("dex", 20);
        set("per", 21);
        set_skill("literate", 60);
        set("chat_chance", 3);
        set("chat_msg", ({
                "吳古賢嘆道：現在的孩子呀，唉！！！！！\n",
                "吳古賢道：老朽已經不中用了，該回老家過過清閒日子了。",
                "吳古賢嘆道：教幾十年的書，學問卻越來越差了，唉。。。。",
        }));
        set("inquiry", ([
                 "戒尺" : "戒尺，這把戒尺我已有十數年未用了。說完，吳古賢長嘆一聲。",
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
