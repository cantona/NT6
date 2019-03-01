// Room: /d/yanping/shuyuan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "延平書院");
        set("long", @LONG
建于宋嘉定二年，郡守陳宓于九峰山麓，仿白鹿書院創建此延平書
院，為“延平四賢”講學之所，書院建于九峰山號稱“金交椅”的山凹
之處。此處“日受千人拜，夜享萬盞燈”，為延平風水絕佳之地。堂上
坐著一個先生，身後是一個書架，擺滿了各種典籍。先生正據案奮筆疾
書，似乎在趕著甚麼學問。原來他就是黃裳啊，他曾修《萬壽道藏》，
無師自通，修習內功外功，竟成為一位武功大高手，寫下了武林無上密
笈《九陰真經》。
LONG );
        set("exits", ([
                "west"      : __DIR__"9fengshan",
                "southeast" : __DIR__"yuandong",
        ]));
        set("objects", ([
                __DIR__"npc/huangshang" : 1,
        ]));
        set("no_fight", 1);
        setup();
        replace_program(ROOM);
}