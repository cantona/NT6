inherit ROOM;
void create()
{
       set("short", "柳綠山莊");
        set("long",
"漸行漸遠，你只覺自己腳下格格作響，似是踢到了什麼東西，又似踩\n"
"碎了什麼東西。你定神一看，原來一地都是白骨，更有些人似乎死去不久，\n"
"全身沒有絲毫血色，全身腐爛了個七七八八，身邊全是兵器看來都是武林\n"
"中人。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "northwest" : __DIR__"yongdao3",
          "south" : __DIR__"yongdao1",
        ]));

        setup();
}
