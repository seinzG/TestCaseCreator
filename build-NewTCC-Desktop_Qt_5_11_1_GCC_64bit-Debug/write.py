import sys
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
SHEET_NAME = sys.argv[1][1:]
SAMPLE_RANGE_NAME = SHEET_NAME + '!A1:A10'


def update_values(spreadsheet_id, range_name, value_input_option, _values):
    print(f"{SAMPLE_RANGE_NAME}")
    creds = Credentials.from_authorized_user_file('token.json', SCOPES)

    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())

        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    try:
        service = build('sheets', 'v4', credentials=creds)
        values = _values
        body = {
            'values': values
        }
        result = service.spreadsheets().values().append(
            spreadsheetId=spreadsheet_id, range=range_name,
            valueInputOption=value_input_option, body=body).execute()
        # return result
    except HttpError as error:
        print(f"An error occurred: {error}")
        return error

    border = {
        'style': 'SOLID',
        'width': 1,
        'color': {
            "alpha": 1.0
        },
    }

    result = service.spreadsheets().values().get(
        spreadsheetId=spreadsheet_id,
        range=f'{SHEET_NAME}!A1:ZZ'
    ).execute()

    values = result.get('values', [])

    row_count = sum(1 for row in values if any(row))
    col_count = sum(1 for col in values[0] if any(col))

    print(f"The number of rows with text in '{SHEET_NAME}' is {row_count}.")
    print(f"The number of col with text in '{SHEET_NAME}' is {col_count}.")

    update_requests = []

    sp = service.spreadsheets().get(
        spreadsheetId=spreadsheet_id
    ).execute()

    sheets = sp['sheets']
    for sheet in sheets:
        if sheet['properties']['title'] == SHEET_NAME:
            sheet_id = sheet['properties']['sheetId']
            break

    for row in range(0, row_count):
        for col in range(0, col_count):
            update_request = {
                'updateBorders': {
                    'range': {
                        'sheetId': sheet_id,
                        'startRowIndex': row,
                        'endRowIndex': row + 1,
                        'startColumnIndex': col,
                        'endColumnIndex': col + 1
                    },
                    'top': border,
                    'bottom': border,
                    'left': border,
                    'right': border
                }
            }
            update_requests.append(update_request)

    request_body = {
        'requests': update_requests
    }

    service.spreadsheets().batchUpdate(
        spreadsheetId=spreadsheet_id,
        body=request_body
    ).execute()

    print('Borders added successfully.')


if __name__ == '__main__':
    args = [string[1:] for string in sys.argv[2:11]]
    SAMPLE_SPREADSHEET_ID = open('spreadsheet_id', 'r').readline().strip()
    update_values(SAMPLE_SPREADSHEET_ID, SAMPLE_RANGE_NAME, 'USER_ENTERED', [args])
