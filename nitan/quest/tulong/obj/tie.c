inherit ITEM;
mapping where_map=([
"gc":"/d/city/guangchang",
"sl":"/d/shaolin/guangchang1",
"bt":"/d/baituo/dating",
"tam":"/d/city2/tian_anm",
"hmy":"/d/heimuya/up1",
"hs":"/d/huashan/zhenyue",
"wd":"/d/wudang/chaotiangong",
"ts":"/d/taishan/nantian",
"xy":"/d/xiaoyao/qingcaop",
"xx":"/d/xingxiu/xxh1",
"xs":"/d/xueshan/dadian",
"shl":"/d/shenlong/dating",
"qz":"/d/quanzhou/zhongxin",
"lj":"/d/lingjiu/dating",
]);
void init(){
add_action("do_trans","trans");
}
void create(){
set_name("魔法傳送帖",({"trans site","site"}));
set_weight(100); set_max_encumbrance(8000);
set("no_drop", "這樣東西不能離開你。\n");
        if( clonep() )                set_default_object(__FILE__);
 else {     set("long",              "一張魔法傳送帖，以它的魔力現在所能到達(trans)的地方如下。\n
\t中央廣場(gc)    少林寺(sl)  白駝山(bt)  天安門(tam) \n
\t黑木崖(hmy)     華山(hs)    武當山(wd)  泰山(ts)    \n
\t逍遙派(xy)      星宿海(xx)  雪山寺(xs)  神龍教(shl) \n
\t泉州(qz)        靈鷲宮(lj)\n");
set("unit","張"); 
set("use_count", 6);}
}
int do_trans(string arg){
        object me,obj;string msg,str;str=where_map[arg];
        if( !arg||!stringp(str)) return notify_fail("你要去哪裡？\n");
me=this_player();
             if( !query("outdoors", environment(me)) )
 return notify_fail("在這房間裡無法使用魔法傳送。\n");
 if (me->is_fighting())
return notify_fail("戰鬥中無法使用魔法傳送！");
str+=".c";
        if(file_size(str)<0) 
return notify_fail("沒有這個地方。\n");
        if (query("use_count") < 1) 
            {
message_vision("魔法傳送帖閃出一道金光，隨後便消失了。\n",me); 
          destruct(this_object());
          return 1;            }
    if( stringp(msg=query("env/msg_mout", me))){if( msg != "")message_vision(msg+"\n",me);}
       else                message_vision("只見一陣煙霧過後，$N的身影已經不見了。\n", me);
me->move(str); 
addn("use_count",-1);if( stringp(msg=query("env/msg_min", me)) )
       {if (msg!="") message_vision(msg+"\n", me);}
        else                message_vision("$N的身影突然出現在一陣煙霧之中。\n", me);        return 1;}