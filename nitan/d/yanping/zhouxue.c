// Room: /d/yanping/zhouxue.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "州學");
        set("long", @LONG
延平府名優薈萃，文風昌盛。明代海瑞曾在此任過教諭。楊時、羅
從彥、李炯、朱熹四大名儒曾在此講學，被後人稱為“延平四賢”，延
平府亦被譽為“理學名邦”、“東南鄒魯”，城內五步一塾，十步一庠，
人才蔚起。宋鹹淳元年（1265年）卅一人同第進士，為古今所罕見。布
衣黃裳為宋神宗元豐五年（l082）壬戌科狀元。他就是奉旨編撰《萬壽
道藏》，悟徹絕世武功，留下《九陰真經》的正主兒。現在他正在延平
書院做他的活兒呢。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"meishanpo",
                "southdown" : __DIR__"xishan",
        ]));
        set("objects", ([
                "/d/taishan/npc/shu-sheng": random(2)+1,
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1450);
        set("coor/y", -6170);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}