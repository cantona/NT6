string place = "";
string the_nation = "";
string the_party = "";
string the_enemy = "";
int all = 0;
string name1,name2,name3;
mixed *story;

int select_quest();
string create_tiaoxin();
string jiuming();
int not_wizard(object ob);

nosave mixed *all_story = ({
({
        "place，繁華之地，name1，name2，name3一行三人正在逛街。",
        "一個流氓匆忙行路中，撞了name1一下，name1反手一個巴掌抽了過去。",
        "很快圍上來好幾個流氓，把name1團團圍住。",
        "name2眼睛一瞪：『想幹嘛？打架？』(卷袖子中...)",
        "流氓們相顧大笑，齊唰唰的抽出雪亮的鋼刀，逼上前來。",
        "name2有些結巴：『我...我們...是...是...the_party的！你們別亂來！』",
        "幾把鋼刀當面劈將過來...",
        "name1嚇了一跳，反身就跑，速度飛快...",
        "一個流氓飛出一把小刀，正中name1屁股，隨著name1的狂奔上下顫抖。",
        "name2見鋼刀劈過來，急忙閃身，衣襟給削掉一片，立刻掉頭逃竄。",
        "走在最前面的name3聽到聲響，剛回頭，看到name1，name2飛也似從身邊竄過。",
        "後面一群流氓揮舞著鋼刀叫喊著追殺過來！",
        "......",
        "name3後發先至，跑在name1，name2前面...",
        "三個人跑的上氣不接下氣，總算擺脫了流氓。",
        "一個時辰後...",
        "一群人手持兵器，沖入place，大街小巷中四處搜索。",
        (: create_tiaoxin :),
        "據說the_enemy最近又重新出現在江湖，個個攜帶了武器，一副要找茬的樣子！",
        "江湖中有人見到他們正在place集結，氣勢洶洶，目空一切的樣子！",
        "據知情人士透露，他們這次打定主意要鏟平the_party！",
        "真是豈有此理，區區跳樑小醜，the_party難道就真的怕了他們不成？",
}),
({
        "name1走在路上，迎面遇到name2，趕緊揚手打招呼。",
        "name2拉著name1的手，鬼鬼祟祟的扯到一個沒人的角落。",
        "name1很驚奇，剛想發問，name2就豎起食指：『噓！...』",
        "name2探頭探腦地四下張望是否有其他人...",
        "『這是我前天從一個流氓屍體上搜出來的』，name2遞給name1一本薄絹小冊。",
         "name1隨手翻了翻，眼珠子瞪得比牛鈴還大！",
         "『這...這是什麼東東？哇，你小子偷看春宮圖？』name1驚奇的大叫起來。",
        "name2嚇的趕緊捂住name1嘴巴：『小聲！小聲點！！』",
        "name2湊到name1耳邊輕聲說到：『看下面的注解，是the_enemy老大和他姘頭哦！』",
        "name2竊竊賊笑：『那可是他手下小嘍羅偷看了畫出來的，不想到了我們手裡，如何？逼真吧？』",
        "name1半天合不上嘴巴，突然叫道：『the_enemy老大幹那事給人偷偷畫下來了？』",
        "name2一把掐住name1脖子，齜牙咧嘴地說：『叫你小聲點！還這麼扯著嗓子嚷嚷，想死啊？』",
        "......",
        "name1面紅氣喘的被name2拖走了。",
        "一扇門打開了，一個腦袋伸出來左右顧盼，小聲嘀咕：『出這麼大的糗事？好在給我聽到了！』",
        "過了數個時辰...",
        "一群人手持兵器，沖入place，大街小巷中四處搜索。",
        (: create_tiaoxin :),
         "據說the_enemy最近又重新出現在江湖，個個攜帶了武器，一副要找茬的樣子！",
        "江湖中有人見到他們正在place集結，氣勢洶洶，目空一切的樣子！",
        "真是豈有此理，區區跳樑小醜，the_party難道就真的怕了他們不成？",
        "據知情人士透露，他們這次打定主意要鏟平the_party！",
}),
({
        "name1，name2上山打獵歸來...",
        "name1：『你不是說山上有紅狐貍麼？怎麼連根野雞毛都沒看到？』",
        "name2白白眼睛：『還不是你一路放屁，別說狐貍，老虎都給你臭跑了！』",
        "name1臉一紅，不甘心地分辯著：『你自己也放了一個的，而且是最臭的那個！』",
        "name2飛起一腳，踹在name1的屁股上，name1一把扯住了name2的頭發....",
         "兩個人打架中......",
         "一個人走下山來，背後披著兩張火紅的狐貍皮。",
        "name1眼睛一亮，對著name2使了個眼神。",
        "name2心領神會，等陌生人走過身邊，突然彎腰撿起一塊石頭沖他後腦勺就是狠狠一下子。",
        "name1沖上前，對準倒在地上的陌生人又用力踹了幾腳！",
        "兩個人得意的姦笑：『這下子不會兩手空空地回去，讓the_party的兄弟笑話了。』",
        "name1和name2一人提著一張狐貍皮揚長而去。",
        "......",
        "一群人手持兵器，沖入place，大街小巷中四處搜索。",
        (: create_tiaoxin :),
        "據說the_enemy最近又重新出現在江湖，個個攜帶了武器，一副要找茬的樣子！",
        "江湖中有人見到他們正在place集結，氣勢洶洶，目空一切的樣子！",
        "據知情人士透露，他們這次打定主意要鏟平the_party！",
        "真是豈有此理，區區跳樑小醜，the_party難道就真的怕了他們不成？",
}),
({
        "name1走在路上，突然前面竄出一個彪形大漢，舉著一把明晃晃的鋼刀！",
        "『大爺我要你錢不要你的命，聰明的話就趕緊把錢袋給我！』",
        "name1兩腿顫抖，掏出錢袋，彪形大漢一把搶過，揚長而去。",
        "name2，name3走來，看見name1臉色蒼白，上前訊問事由。",
        "『靠，什麼鳥膽子這麼大，欺負到我們the_party頭上了？！』，name2義憤填膺。",
         "name3冷冷一笑，一揮手：『追！』",
         "......",
        "三個人追上大漢，團團圍住。",
        "name2突然彎身抓起一把泥土，劈面向大漢臉上洒去。",
        "name3乘大漢眼睛無法睜開，張開一個大麻布袋將大漢上半身套了進去，旋即收緊袋口。",
        "name1得意的大笑，操起一根棍子就沒頭沒臉地狠揍。",
        "片刻之後，name3將麻布袋扯回來，大漢給揍得跟豬頭一樣。",
        "『給我記住，以後見到the_party的人最好躲著走路！』，name2揚手又送上了一個大嘴巴。",
        "name1將自己的錢袋掏了回來，順帶把大漢口袋裡的散碎銀兩搜刮一空。",
        "三個人高高興興的去找館子喝酒。",
        "片刻之後...",
        "一群人手持兵器，沖入place，大街小巷中四處搜索。",
        (: create_tiaoxin :),
         "據說the_enemy最近又重新出現在江湖，個個攜帶了武器，一副要找茬的樣子！",
        "江湖中有人見到他們正在place集結，氣勢洶洶，目空一切的樣子！",
        "據知情人士透露，他們這次打定主意要鏟平the_party！",
        "真是豈有此理，區區跳樑小醜，the_party難道就真的怕了他們不成？",
}),
});