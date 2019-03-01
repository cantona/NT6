inherit ROOM;

void create()
{
        set("short", "冰雪軒");
        set("long", @LONG
這裡是凌霄城裡最大的酒樓冰雪軒，同時也是凌霄城的名跡
之一。大凡過往旅客，不管是販夫走卒，還是文人墨客，遷客騷
人，都要到此一醉。當年謝煙客獨闖凌霄城，在此狂飲十八壇烈
酒之後，殺入凌霄內城。從此，凌霄城冰雪軒的大名，便是名聞
四海。
LONG);
        set("exits", ([
                "east" : __DIR__"iceroad1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/dizi" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
