# May 31, 2022
I created a prototype for the project using a 16x2 LCD. I managed to print "Hello World!" on the screen with an animation.
The code for this project is from JohnInTX on a forum page. Here is the link to the thread: https://forum.allaboutcircuits.com/threads/pic16f1459-lcd-pc1602lrs-config.113483/

<img src="https://attachments.office.net/owa/da640190%40wellingtoncdsb.ca/service.svc/s/GetAttachmentThumbnail?id=AAMkADNhOTNlMzRmLTQxOTEtNGE3Zi04MTFlLTJmNGFmOTk3Y2Q3OABGAAAAAADgO7PMOUrZRZkIDPs2294YBwD%2Bt4uwjUKQRYFZsHdYzGl%2BAAAAAAEMAAD%2Bt4uwjUKQRYFZsHdYzGl%2BAAQDZazSAAABEgAQAJPh8XzJadlBrgHRSbnDUkI%3D&amp;thumbnailType=2&amp;token=eyJhbGciOiJSUzI1NiIsImtpZCI6IkZBRDY1NDI2MkM2QUYyOTYxQUExRThDQUI3OEZGMUIyNzBFNzA3RTkiLCJ0eXAiOiJKV1QiLCJ4NXQiOiItdFpVSml4cThwWWFvZWpLdDRfeHNuRG5CLWsifQ.eyJvcmlnaW4iOiJodHRwczovL291dGxvb2sub2ZmaWNlLmNvbSIsInVjIjoiNmRlYjY4OTkwYjE4NGQ5MjlmZGJiNzE4NWZkMjMyMDgiLCJzaWduaW5fc3RhdGUiOiJbXCJrbXNpXCJdIiwidmVyIjoiRXhjaGFuZ2UuQ2FsbGJhY2suVjEiLCJhcHBjdHhzZW5kZXIiOiJPd2FEb3dubG9hZEBkZDZhODc1Ni0yYTE3LTQ3NjUtODI2ZC01NmJhZDJiODA4ZWIiLCJpc3NyaW5nIjoiV1ciLCJhcHBjdHgiOiJ7XCJtc2V4Y2hwcm90XCI6XCJvd2FcIixcInB1aWRcIjpcIjExNTM4MzYyOTY1MjgwMzA5MDhcIixcInNjb3BlXCI6XCJPd2FEb3dubG9hZFwiLFwib2lkXCI6XCJiNTk1OWYwZi0yM2I5LTRmZmMtOTk0Ni1lMTc0OWJmNTFiMjVcIixcInByaW1hcnlzaWRcIjpcIlMtMS01LTIxLTI2NDI1NzIwMDUtMjc4ODI3MTIwNi0zNTU1MjE3MzcyLTg2NTQwN1wifSIsIm5iZiI6MTY1NDAyOTMwNCwiZXhwIjoxNjU0MDI5OTA0LCJpc3MiOiIwMDAwMDAwMi0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDBAZGQ2YTg3NTYtMmExNy00NzY1LTgyNmQtNTZiYWQyYjgwOGViIiwiYXVkIjoiMDAwMDAwMDItMDAwMC0wZmYxLWNlMDAtMDAwMDAwMDAwMDAwL2F0dGFjaG1lbnRzLm9mZmljZS5uZXRAZGQ2YTg3NTYtMmExNy00NzY1LTgyNmQtNTZiYWQyYjgwOGViIiwiaGFwcCI6Im93YSJ9.FZ_kUOWWU7a1nr-z3v9nHnhFXAMiNH1BJ1n4_erMZajoKp0xZ9PD56GB33Z8JWYXv6XKhtb0FEgB_iir6oaJRgvWjxi0zWU95myDWq-u7_Tz3AjskIEAOGBDl8b2BaqeA2ESC8qa1RIePYe1YrNShdxafz3cPTmd-ucLx8Fqi0iVzr3Y8f-ErNJeUacTLn1XrcZNmnMAf9GlB_WBwdD3uhCZeANRQ0kIV6KXOHk7Ev031jmGUyzwxR-CbuYMbcIWbr0Pc51S6SbZj3Ry2l022n_RrBQnjHVOnbEPNP2xUicQ0PRpJGTFfZqcaLVDiNTp06-42sEy_eJXqaMBAVYRXg&amp;X-OWA-CANARY=tOwqLSzMMUmG5EIrRNFP3uA7gh9FQ9oY17luUO1Jbu0jGq6zgsRlcIEM-aKIRQCiFbeiXwU5_mg.&amp;owa=outlook.office.com&amp;scriptVer=20220513004.21&amp;animation=true" alt="Image preview"/>![image](https://user-images.githubusercontent.com/99228002/171282242-377216f5-773a-4680-8938-8002919bb5e0.png)

# June 2, 2022
I figured out how to create custom characters for the LCD.

# June 7, 2022
I added a joystick to the project. I was able to test the joystick by making a stick figure move on the screen.
The animation works by clearing or earasing the characters on the display and showing the character in its
updated location. Here is an image of the project currently:

<img src="https://attachments.office.net/owa/da640190%40wellingtoncdsb.ca/service.svc/s/GetAttachmentThumbnail?id=AAMkADNhOTNlMzRmLTQxOTEtNGE3Zi04MTFlLTJmNGFmOTk3Y2Q3OABGAAAAAADgO7PMOUrZRZkIDPs2294YBwD%2Bt4uwjUKQRYFZsHdYzGl%2BAAAAAAEMAAD%2Bt4uwjUKQRYFZsHdYzGl%2BAAQIJlDbAAABEgAQAJHgFK3oBi5PoM1WIXLr28g%3D&amp;thumbnailType=2&amp;token=eyJhbGciOiJSUzI1NiIsImtpZCI6IkZBRDY1NDI2MkM2QUYyOTYxQUExRThDQUI3OEZGMUIyNzBFNzA3RTkiLCJ0eXAiOiJKV1QiLCJ4NXQiOiItdFpVSml4cThwWWFvZWpLdDRfeHNuRG5CLWsifQ.eyJvcmlnaW4iOiJodHRwczovL291dGxvb2sub2ZmaWNlLmNvbSIsInVjIjoiN2ViNTA0YWE3NDVhNGQwMWI4ZWY0NTJkYjkyODQ1ZTAiLCJzaWduaW5fc3RhdGUiOiJbXCJrbXNpXCJdIiwidmVyIjoiRXhjaGFuZ2UuQ2FsbGJhY2suVjEiLCJhcHBjdHhzZW5kZXIiOiJPd2FEb3dubG9hZEBkZDZhODc1Ni0yYTE3LTQ3NjUtODI2ZC01NmJhZDJiODA4ZWIiLCJpc3NyaW5nIjoiV1ciLCJhcHBjdHgiOiJ7XCJtc2V4Y2hwcm90XCI6XCJvd2FcIixcInB1aWRcIjpcIjExNTM4MzYyOTY1MjgwMzA5MDhcIixcInNjb3BlXCI6XCJPd2FEb3dubG9hZFwiLFwib2lkXCI6XCJiNTk1OWYwZi0yM2I5LTRmZmMtOTk0Ni1lMTc0OWJmNTFiMjVcIixcInByaW1hcnlzaWRcIjpcIlMtMS01LTIxLTI2NDI1NzIwMDUtMjc4ODI3MTIwNi0zNTU1MjE3MzcyLTg2NTQwN1wifSIsIm5iZiI6MTY1NDY1MTc1MCwiZXhwIjoxNjU0NjUyMzUwLCJpc3MiOiIwMDAwMDAwMi0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDBAZGQ2YTg3NTYtMmExNy00NzY1LTgyNmQtNTZiYWQyYjgwOGViIiwiYXVkIjoiMDAwMDAwMDItMDAwMC0wZmYxLWNlMDAtMDAwMDAwMDAwMDAwL2F0dGFjaG1lbnRzLm9mZmljZS5uZXRAZGQ2YTg3NTYtMmExNy00NzY1LTgyNmQtNTZiYWQyYjgwOGViIiwiaGFwcCI6Im93YSJ9.D3C6fS7WZ6wRUFohneeHJGQDNPoWU235dhi8lm5-X540hO8axFyuufUpcm8MiBcTckR05vCAVVEycXlWt9_ranIrJZGAekUtCBkZhD8VNvW2gKoqtmQnMgAyc32HmpYhCYvkP6YfnFWGMIlEmkEQ7ELd41SZ6rt6qW0yxi1LIf2j1Q4OjV-Gsz6XdctVgTO6GKeCct0BYA4_qQygtE-_Uhp2_J1PxiZHZiynTwc89u2xNBWK5deotzQgK6iAvs8S7ldjq47KLY6QibO3nVwFqX8Q2GueORTHXxhMChHS05s_BnC_qYzCnRF1IuUoJj0F5B2yu04Ga2lBr6ttetqwKg&amp;X-OWA-CANARY=fBTfffEP0Eaeeaw9P_NQgfAPI1juSNoY6KOIFQwsLuQcX9OFWl6rjkfVjKTYfbWEu0b2k-JW2wk.&amp;owa=outlook.office.com&amp;scriptVer=20220527002.09&amp;animation=true" alt="Image preview"/>![image](https://user-images.githubusercontent.com/99228002/172513033-9a675a3e-0f11-42ad-a848-1aa8f5a5b74a.png)

# June 10, 2022
I created the google dinosaur game for the console. It has a dinosaur that jumps using the joystick, a cactus and a bird to avoid, and the game gets
progressively faster as time goes on. The score and game over screen don't work yet. I will try to create a working menu select screen where you can select the game.
Also a working game over screen that displays your score.

# June 14, 2022
I created a proper game over screen that displays the score. Once I add sound effects to the dino game I will try to make a second game. The second one will probably be just as basic as the first. I also added a rand() function to the postion of the cactus and bird, so it should be in a different postion every play, but I can't
really tell if it is workng.

# June 15, 2022
I started to create a second game. I was having difficulty configuring the joystick because the second game will require both the x and y input.

# June 21, 2022
I have almost finished the second game. I perfected the movement shooting and I even figured out the issue with the rand() function.
After I have perfected this game to my liking I am going to try to clean up the repository. I will try to make the documentation more clear
and put code into sperate files rather than one giant main file.

# June 22, 2022
Here is the final product: 
![image](https://user-images.githubusercontent.com/99228002/175141323-3cfa681c-8100-437f-9919-842ad224c8f6.png)

