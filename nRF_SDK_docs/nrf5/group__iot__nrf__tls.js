var group__iot__nrf__tls =
[
    [ "nrf_tls_instance_t", "structnrf__tls__instance__t.html", [
      [ "instance_id", "structnrf__tls__instance__t.html#a8ac6f432bc6457caff75c7f00c03e3c0", null ],
      [ "transport_id", "structnrf__tls__instance__t.html#aced5fb6b4f58cc9d4a295e360d6e50c8", null ]
    ] ],
    [ "nrf_tls_preshared_key_t", "structnrf__tls__preshared__key__t.html", [
      [ "identity_len", "structnrf__tls__preshared__key__t.html#a1091a8eef107b7a96d8ef969bb60d684", null ],
      [ "p_identity", "structnrf__tls__preshared__key__t.html#ac3cc9d619d062be40d28ebca78dbcc79", null ],
      [ "p_secret_key", "structnrf__tls__preshared__key__t.html#a856e83b5dfa6ec19253bdb8f2e576c1f", null ],
      [ "secret_key_len", "structnrf__tls__preshared__key__t.html#a29b8a54d87ed05ac04f9add229c150c3", null ]
    ] ],
    [ "nrf_tls_raw_key_t", "structnrf__tls__raw__key__t.html", [
      [ "p_private_key", "structnrf__tls__raw__key__t.html#a7f03367c5fab88be4e7f61fde41c9941", null ],
      [ "p_public_key", "structnrf__tls__raw__key__t.html#a2b0469f665618232a85677e35aff41ce", null ],
      [ "private_key_len", "structnrf__tls__raw__key__t.html#a7cd96c8fc36f74d1297ca41862f5a767", null ],
      [ "public_key_len", "structnrf__tls__raw__key__t.html#a39bd74a03c8de4b95b365f1721b348ca", null ]
    ] ],
    [ "nrf_tls_certificate_t", "structnrf__tls__certificate__t.html", [
      [ "certificate_len", "structnrf__tls__certificate__t.html#a53e5f84e010874ad17818dd00c0221eb", null ],
      [ "p_certificate", "structnrf__tls__certificate__t.html#ac6a4c738d4f5d6a7771ef95dd99d0316", null ],
      [ "p_private_key", "structnrf__tls__certificate__t.html#a091bbd772e8ea9e1730ec7566101bcb9", null ],
      [ "private_key_len", "structnrf__tls__certificate__t.html#a68db4a23929642956abab9edc8c00b4b", null ]
    ] ],
    [ "nrf_tls_key_settings_t", "structnrf__tls__key__settings__t.html", [
      [ "ca_cert_pem_len", "structnrf__tls__key__settings__t.html#a439c2ff275d2c7c44a1d3ef604d84a5b", null ],
      [ "p_ca_cert_pem", "structnrf__tls__key__settings__t.html#afb4964fdc3e5c7dda497d6df73313c1a", null ],
      [ "p_own_certificate", "structnrf__tls__key__settings__t.html#adada8c7616831a69197a84bdafb06008", null ],
      [ "p_psk", "structnrf__tls__key__settings__t.html#acd58b48beeb0bcf50e6f7b8fe936e5c9", null ],
      [ "p_raw_key", "structnrf__tls__key__settings__t.html#aa00539371fe44f0262ed6ecc61a511b8", null ]
    ] ],
    [ "nrf_tls_options_t", "structnrf__tls__options__t.html", [
      [ "output_fn", "structnrf__tls__options__t.html#a451665382c14c02a218ffb3da8fdce07", null ],
      [ "p_key_settings", "structnrf__tls__options__t.html#a6897c15711e572e6ab14cfc733eca4ff", null ],
      [ "role", "structnrf__tls__options__t.html#ace8bb7b05c9cf5174cf1dc08c858d336", null ],
      [ "transport_type", "structnrf__tls__options__t.html#a67bd12a22393a8afb824bef0ae133cc6", null ]
    ] ],
    [ "NRF_TLS_INTSANCE_INIT", "group__iot__nrf__tls.html#ga45db421b9008486832ec3cd1232435a7", null ],
    [ "NRF_TLS_INVALID_INSTANCE_IDENTIFIER", "group__iot__nrf__tls.html#ga979d1567885d6340f3f5f15483d3bd97", null ],
    [ "nrf_tls_output_t", "group__iot__nrf__tls.html#gac8b9aaa06755c2e333fb1eeff423918a", null ],
    [ "nrf_tls_role_t", "group__iot__nrf__tls.html#gabbd56e3e604cd307c60a2b21faacbb25", [
      [ "NRF_TLS_ROLE_CLIENT", "group__iot__nrf__tls.html#ggabbd56e3e604cd307c60a2b21faacbb25a34993696abe39fe7df8c8912e50c579b", null ],
      [ "NRF_TLS_ROLE_SERVER", "group__iot__nrf__tls.html#ggabbd56e3e604cd307c60a2b21faacbb25aa75706da3052c97d409625fe521d0aa9", null ]
    ] ],
    [ "nrf_transport_type_t", "group__iot__nrf__tls.html#ga427594edb043eb4b0f44a95756ea6db2", [
      [ "NRF_TLS_TYPE_STREAM", "group__iot__nrf__tls.html#gga427594edb043eb4b0f44a95756ea6db2a20c585798c62d99b409e199a7e358f57", null ],
      [ "NRF_TLS_TYPE_DATAGRAM", "group__iot__nrf__tls.html#gga427594edb043eb4b0f44a95756ea6db2abfee38d4ff151bac9add7fc183fa162a", null ]
    ] ],
    [ "nrf_tls_alloc", "group__iot__nrf__tls.html#gacd6ba4436554baf572b37121d5f27e0b", null ],
    [ "nrf_tls_free", "group__iot__nrf__tls.html#gad76e480870511ed3062320bcb313bb09", null ],
    [ "nrf_tls_init", "group__iot__nrf__tls.html#ga105132616e713c334e3dc2b371b0a7e8", null ],
    [ "nrf_tls_input", "group__iot__nrf__tls.html#gaa328f63bbc533db0904ed1c8fb3d42f2", null ],
    [ "nrf_tls_process", "group__iot__nrf__tls.html#ga542332cddc334c70bb842a9b732965f4", null ],
    [ "nrf_tls_read", "group__iot__nrf__tls.html#ga0ca87c51875a1e206d50ab9277dae867", null ],
    [ "nrf_tls_write", "group__iot__nrf__tls.html#gaf4f847174293863c1b546fae8337cc75", null ]
];