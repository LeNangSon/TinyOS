.global trap_entry
trap_entry:
    # lưu context
    call trap_handle
    # trả ngữ cảnh quay lại luồng chính