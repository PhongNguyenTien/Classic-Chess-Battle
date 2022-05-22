# Classic-Chess-Battle
A simple program which is relevant to SDL2 library and C++.
## Hướng dẫn cài đặt 
- Tạo 1 folder mới, đặt tên là Classic Chess Battle.
- Trong Visual Studio 2022, chọn Clone a Repository trong mục Get Started.
- Tại mục Repository Location, dán đường link https://github.com/PhongNguyenTien/Classic_Chess.git .
- Tại mục Path, nhấn chuột vào dấu ba chấm bên phải, chọn thư mục Classic Chess Battle vừa tạo, rồi nhấn Select Folder, sau đó nhấn Clone.
- Sau khi đã clone xong, mở file Classic Chess Battle.sln trong phần Solution Explorer.
- Trong project Classic Chess có chứa các file .cpp và file .h, nhấn vào Local Windows Debugger để chạy chương trình.
## Mô tả chung về trò chơi
- Game cờ vua cổ điển 2 người chơi.
- Trò chơi được cài đặt theo luật cờ vua hiện hành.
## Các chức năng đã cài đặt
- Đánh dấu cho người chơi có thể biết được những nước đi và ăn quân hợp lệ trong game.
- Ở mỗi bên, khi quân vua bị chiếu, chỉ những nước đi thỏa mãn vua không bị ăn mới được đánh dấu.
- Có chức năng phong cấp cho tốt và chức năng nhập thành.
- Báo hiệu game kết thúc khi 1 trong 2 bên bị chiếu hết hoặc hòa cờ.
- Link video demo: https://youtu.be/3izpdRbbvrI
## Các kĩ thuật được sử dụng
- Chương trình chạy trên C++14, x64, Visual Studio 2022.
- Thư viện đồ họa: SDL2, SDL2_image
- Kĩ thuật lập trình được sử dụng:
  - Mảng, duyệt mảng. 
  - Con trỏ
  - Cấu trúc, lớp, kế thừa lớp.
  - Vector, thêm phần tử vào vector.
## Kết luận
- Chương trình đơn giản, không sử dụng những cấu trúc dữ liệu phức tạp, tuy nhiên trong game phải cài đặt tương đối nhiều trường hợp vể điều kiện di chuyển của các quân cờ.
- Về chất lượng đồ họa: tạm chấp nhận được, đủ để người chơi dễ dàng chơi.
- Về code: đã được refactor, tuy nhiên vẫn còn một số code của hàm chức năng còn dài và phức tạp.
- Khi làm việc với thư viện đồ họa SDL2 ta phải quản lí nhiều chi tiết đồ họa nhỏ trong game bên cạnh những logic chương trình chính.
## Hướng phát triển
- Tìm hiểu và bổ sung thêm AI cho game, bổ sung chế độ người đấu với máy.
- Cải thiện phần đồ họa để game bắt mắt và sinh động hơn.
## Những điều tâm đắc khi làm game Classic_Chess
- Biết thêm về cách chơi cờ vua.
- Biết cách triển khai chương trình thành các file nhỏ hơn, qua đó quản lí code cũng như sửa lỗi dễ dàng hơn.
- Trước khi bắt đầu viết code 1 chương trình có nhiều đối tượng như game, việc hình dung game có những đối tượng nào và vạch rõ từng đặc điểm về từng đối tượng sẽ giúp viết code các chức năng của đối tượng dễ dàng hơn rất nhiều.
- Học hỏi từ các bạn xung quanh là cách tuyệt vời để có thêm kiến thức.
