//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "書舖");
        set ("long", @LONG
這是荊州城裡的一家書舖，平時生意頗為冷清，最近卻來了不少江
湖豪客，嚷嚷著要買《唐詩選輯》，即便提價到五兩銀子一本，也爭先
恐後地掏錢，惟恐買遲了就沒有了。店裡的伙計在忙著招呼客人，眉開
眼笑地收錢找錢。幾個身上帶刀帶劍、挺胸凸肚的練把式爺們在粗聲大
氣地討論著什麼，時而停下來急急翻動手裡的書，似乎那書裡有什麼天
大的秘密。
LONG);
        set("exits", ([ 
                "west" : __DIR__"beidajie2",
        ]));
        set("objects", ([
                "/d/huashan/npc/haoke"  : 2,
                "/d/taishan/npc/jian-ke": 1,
                "/d/taishan/npc/dao-ke" : 1,
        ]));

        set("coor/x", -7090);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}