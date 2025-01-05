# tokyo weili robot competition
This is one of the sub-repositories of a project created for participation in the Tokyo Welcoming Robots competition.
## sub-repositories
**[wheel_tokyo_weili](https://github.com/zisheng7777/wheel_tokyo_weili)**： writer: [林子勝](https://github.com/zisheng7777) <br>
**[tel_first_half](https://github.com/zisheng7777/tel_first_half)**： writer: [洪祐鈞](https://github.com/Sylvexia) <br>
**[dynamixel_control](https://github.com/zisheng7777/dynamixel_control)**： writer: 楊祐陞 <br>

## how to use wheel_tokyo_weili
使用 publish 傳遞 wheel_planner.msg進行控制機器人<br>
topic名稱 /wheel/planner<br>
<br>
distance_x y z(單位:公分)<br>
決定機器人的移動方向跟移動距離<br>
<br>
velocity_x y z(xy速度最快不要超過0.5，z最多不要超過1)<br>
決定機器人的移動方向(持續給值會一直前進，給0會停止)<br>
<br>
far_left far_right (bool)<br>
true決定移動到最左邊或最右邊場地<br>

------------------------------------------------------<br>

使用 subscribe 接收 waitforidle.msg接收機器人移動狀態<br>
topic名稱 /wheel/waitforidle<br>
<br>
waitforidle(bool)<br>
回傳 ture -> 機器人已完成指令動作，可以接收新指令<br>
回傳 false -> 機器人正在進行動作，無法接收新指令<br>
