import os

def create_folders(base_path="."):
    """
    Создаёт папки в указанной директории.
    
    Args:
        base_path: путь к директории (по умолчанию - текущая)
    """
    folders = [
        "A. Зацикленный плейлист",
        "B. Общая длина",
        "C. Город Че",
        "D. Стильная одежда",
        "E. Рюкзак на отрезке",
        "F. Подстроки из карточек",
        "G. Не очень грубая подстрока",
        "H. A-B Рюкзак",
        "I. Отрезок с нужным подмножеством"
    ]
    
    # Создаём полные пути
    for folder in folders:
        full_path = os.path.join(base_path, folder)
        try:
            os.makedirs(full_path, exist_ok=False)
            print(f"✅ Создана: {full_path}")
        except FileExistsError:
            print(f"⚠️ Уже существует: {full_path}")
    
    print(f"\n✨ Создано {len(folders)} папок в {os.path.abspath(base_path)}")

if __name__ == "__main__":
    # Можно указать свой путь, например:
    # create_folders("/home/user/my_folder")
    create_folders()  # Создаст в текущей директории